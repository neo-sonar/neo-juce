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
        std::transform(f, l, std::begin(chunk), [](T x) { return static_cast<float>(x); });

        queue.try_enqueue(chunk);
    }
}
} // namespace

DownSamplingAnalyzer::DownSamplingAnalyzer(std::size_t downSampleFactor) : _downSampleFactor { downSampleFactor }
{
    _buffer.resize(128U);
    startTimerHz(25);
}

auto DownSamplingAnalyzer::process(juce::AudioBuffer<float> const& buffer) -> void
{
    processDownSamplingAnalyzer<decltype(_queue), juce::AudioBuffer<float>, ChunkSize>(
        _queue, buffer, _downSampleFactor);
}

auto DownSamplingAnalyzer::process(juce::AudioBuffer<double> const& buffer) -> void
{
    processDownSamplingAnalyzer<decltype(_queue), juce::AudioBuffer<double>, ChunkSize>(
        _queue, buffer, _downSampleFactor);
}

auto DownSamplingAnalyzer::buffer() const noexcept -> Span<float const> { return _buffer; }

auto DownSamplingAnalyzer::timerCallback() -> void
{
    auto chunk = StaticVector<float, ChunkSize> {};
    if (_queue.try_dequeue(chunk)) {
        // Remove oldest elements & insert new
        auto oldFirst = std::rotate(begin(_buffer), begin(_buffer) + chunk.size(), end(_buffer));
        std::copy(std::begin(chunk), std::end(chunk), oldFirst);

        // Notify UI elements
        sendChangeMessage();
    }
}

} // namespace mc
