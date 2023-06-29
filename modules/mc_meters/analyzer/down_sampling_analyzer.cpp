namespace mc {

namespace {

template <typename Queue, typename Buffer, std::size_t ChunkSize>
auto processDownSamplingAnalyzer(Queue& queue, Buffer const& buffer, std::size_t downSampleFactor) -> void
{
    using T = typename Buffer::SampleType;

    auto const* data      = buffer.getReadPointer(0);
    auto const numSamples = static_cast<std::size_t>(buffer.getNumSamples());

    auto scratchBuffer         = std::array<T, 4096U> {};
    auto const downSampledSize = downSample(data, numSamples, scratchBuffer.data(), downSampleFactor);

    auto const numChunks = (downSampledSize + (ChunkSize - 1U)) / ChunkSize;
    for (auto i = std::size_t { 0 }; i < numChunks; ++i) {
        auto const s = std::min<std::size_t>(ChunkSize, downSampledSize - i * ChunkSize);
        auto const f = scratchBuffer.data() + i * ChunkSize;
        auto const l = scratchBuffer.data() + i * ChunkSize + s;

        auto chunk = StaticVector<float, ChunkSize>(s, 0.0F);

        // We use transform instead of copy, so that we can explicitly
        // cast the value to the type required by the queue chunks.
        // i.e. float <-> double conversion.
        ranges::transform(f, l, ranges::begin(chunk), [](T x) { return static_cast<float>(x); });

        queue.try_enqueue(chunk);
    }
}
} // namespace

DownSamplingAnalyzer::DownSamplingAnalyzer(std::size_t downSampleFactor) : _downSampleFactor { downSampleFactor }
{
    _buffer.resize(128U);
    startTimerHz(25);
}

auto DownSamplingAnalyzer::prepare(juce::dsp::ProcessSpec const& spec) -> void
{
    auto const cutoff = static_cast<float>(spec.sampleRate) / (static_cast<float>(_downSampleFactor * 2UL));
    _filter.setCutoffFrequency(cutoff);
    _filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
    _filter.prepare(spec);

    _filterBuffer.setSize(static_cast<int>(spec.numChannels), static_cast<int>(spec.maximumBlockSize));
}

auto DownSamplingAnalyzer::process(juce::AudioBuffer<float> const& buffer) -> void
{
    _filterBuffer.setSize(buffer.getNumChannels(), buffer.getNumSamples());
    auto inBlock  = juce::dsp::AudioBlock<float const> { buffer };
    auto outBlock = juce::dsp::AudioBlock<float> { _filterBuffer };
    _filter.process(juce::dsp::ProcessContextNonReplacing<float> { inBlock, outBlock });
    processDownSamplingAnalyzer<decltype(_queue), juce::AudioBuffer<float>, chunkSize>(
        _queue, _filterBuffer, _downSampleFactor);
}

auto DownSamplingAnalyzer::reset() -> void { }

auto DownSamplingAnalyzer::buffer() const noexcept -> std::span<float const> { return _buffer; }

auto DownSamplingAnalyzer::timerCallback() -> void
{
    auto newData = false;
    for (auto i { 0U }; i < _queue.size_approx() + 1U; ++i) {
        auto chunk = StaticVector<float, chunkSize> {};
        if (not _queue.try_dequeue(chunk)) { continue; }

        // Remove oldest elements & insert new
        newData       = true;
        auto oldFirst = std::rotate(begin(_buffer), std::next(begin(_buffer), (int)chunk.size()), end(_buffer));
        ranges::copy(chunk, oldFirst);
    }
    if (newData) {
        // Notify UI elements
        sendChangeMessage();
    }
}

} // namespace mc
