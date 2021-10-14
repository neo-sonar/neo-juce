namespace mc {

namespace {

MC_NODISCARD auto sizeAfterDownSample(std::size_t signalSize, std::size_t factor) noexcept -> std::size_t
{
    return (signalSize - 1U) / factor + 1U;
}

template <typename T>
auto downSample(T const* in, std::size_t sizeIn, T* out, std::size_t factor) -> std::size_t
{
    if (factor == 0) { std::copy(in, in + static_cast<std::size_t>(sizeIn), out); }
    auto const n = sizeAfterDownSample(sizeIn, factor);
    for (std::size_t i = 0; i < n; ++i) { out[i] = in[i * factor]; }
    return n;
}

template <typename Queue, typename Buffer, std::size_t ChunkSize>
auto processOscilloscopeImpl(Queue& queue, Buffer const& buffer, std::size_t downSampleFactor) -> void
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

        auto chunk = StaticVector<float, ChunkSize>(s, 0.0f);

        // We use transform instead of copy, so that we can explicitly
        // cast the value to the type required by the queue chunks.
        // i.e. float <-> double conversion.
        std::transform(f, l, std::begin(chunk), [](T x) { return static_cast<float>(x); });

        queue.try_enqueue(chunk);
    }
}
} // namespace

OscilloscopeSource::OscilloscopeSource()
{
    currentScope_.resize(128U);
    startTimerHz(25);
}

auto OscilloscopeSource::process(juce::AudioBuffer<float> const& buffer) -> void
{
    processOscilloscopeImpl<decltype(queue_), juce::AudioBuffer<float>, ChunkSize>(queue_, buffer, downSampleFactor_);
}

auto OscilloscopeSource::process(juce::AudioBuffer<double> const& buffer) -> void
{
    processOscilloscopeImpl<decltype(queue_), juce::AudioBuffer<double>, ChunkSize>(queue_, buffer, downSampleFactor_);
}

auto OscilloscopeSource::currentScope() const noexcept -> span<float const> { return currentScope_; }

auto OscilloscopeSource::timerCallback() -> void
{
    auto chunk = StaticVector<float, ChunkSize> {};
    if (queue_.try_dequeue(chunk)) {
        // Remove oldest elements & insert new
        auto oldFirst = std::rotate(begin(currentScope_), begin(currentScope_) + chunk.size(), end(currentScope_));
        std::copy(std::begin(chunk), std::end(chunk), oldFirst);

        // std::fill(begin(currentScope_), end(currentScope_), 0.0f);
        // DBG(jformat("DEQUEUED: {} / {}", size(chunk), size(currentScope_)));

        // Notify UI elements
        sendChangeMessage();
    }
}

} // namespace mc