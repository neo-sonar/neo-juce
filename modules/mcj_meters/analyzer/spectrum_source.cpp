namespace mc {

static auto frequencyToX(float minFreq, float maxFreq, float freq, float width)
{
    auto const logMinFreq = std::log10(minFreq);
    auto const diff       = std::log10(freq) - logMinFreq;
    return diff * width / (std::log10(maxFreq) - logMinFreq);
}

static auto amplitudeToY(float amplitude, const juce::Rectangle<float> bounds) -> float
{
    auto const infinity = -60.0F;
    auto const dB       = juce::Decibels::gainToDecibels(amplitude, infinity);
    return juce::jmap(dB, infinity, 0.0F, bounds.getBottom(), bounds.getY());
}

SpectrumSource::SpectrumSource(juce::TimeSliceThread& worker, int fftOrder)
    : _worker { worker }
    , _fft(fftOrder)
    , _windowing { size_t(_fft.getSize()), juce::dsp::WindowingFunction<float>::hann, true }
    , _queue { 64 }
{
    _monoBuffer.resize(static_cast<std::size_t>(_fft.getSize()));
    _fftBuffer.resize(static_cast<std::size_t>(_fft.getSize() * 2));
}

SpectrumSource::~SpectrumSource() { reset(); }

auto SpectrumSource::prepare(juce::dsp::ProcessSpec const& spec) -> void
{
    reset();

    _spec = spec;
    _averager.resize(3, static_cast<std::size_t>(_fft.getSize() / 2 + 1));
    _shouldExit.store(false);
    _worker.addTimeSliceClient(this);
}

auto SpectrumSource::reset() -> void
{
    _shouldExit.store(true);
    _worker.removeTimeSliceClient(this);
    _averager.clear();
}

auto SpectrumSource::makePath(juce::Rectangle<float> bounds) -> juce::Path
{
    auto const minFrequency = 20.0F;
    auto const maxFrequency = static_cast<float>(_spec.sampleRate) / 2.0F;

    auto const size = static_cast<int>(_fft.getSize() / 2 + 1);
    auto average    = Vector<float>((size_t)size, 0.0F);

    {
        auto const lock = std::unique_lock { _renderMutex };
        ranges::copy(_averager.average(), ranges::begin(average));
    }

    auto p = juce::Path {};
    p.preallocateSpace(8 + size * 3);

    auto i { 0U };
    while (frequencyForBin<float>(_fft.getSize(), i, _spec.sampleRate) < minFrequency) { ++i; }

    auto const width  = bounds.getWidth();
    auto const freq   = frequencyForBin<float>(_fft.getSize(), i, _spec.sampleRate);
    auto const startY = amplitudeToY(average[i], bounds);
    auto const startX = frequencyToX(minFrequency, maxFrequency, freq, width);
    p.startNewSubPath(bounds.getX() + startX, startY);

    for (; i < average.size(); ++i) {
        auto const frequency = frequencyForBin<float>(_fft.getSize(), i, _spec.sampleRate);
        auto const y         = amplitudeToY(average[i], bounds);
        p.lineTo(bounds.getX() + frequencyToX(minFrequency, maxFrequency, frequency, width), y);
    }

    return p;
}

auto SpectrumSource::useTimeSlice() -> int
{
    dequeueBuffers();
    if (_shouldExit.load()) { return -1; }
    return 0;
}

auto SpectrumSource::processInternal(juce::dsp::AudioBlock<float> const& block) -> void
{
    auto samplesRemaining = block.getNumSamples();

    while (true) {
        if (samplesRemaining <= 0) { return; }
        auto const nextBlockSize = std::min(maxSubBlockSize, samplesRemaining);

        auto subBuffer = StaticVector<float, maxSubBlockSize> {};
        for (std::size_t j = 0; j < nextBlockSize; ++j) {

            auto sample      = 0.0F;
            auto const index = block.getNumSamples() - samplesRemaining + j;
            for (std::size_t ch = 0; ch < block.getNumChannels(); ++ch) { sample += channel(block, ch)[index]; }
            subBuffer.push_back(sample / (float)block.getNumChannels());
        }

        samplesRemaining -= nextBlockSize;
        _queue.try_enqueue(subBuffer);
    }
}

auto SpectrumSource::dequeueBuffers() -> void
{
    auto block = StaticVector<float, maxSubBlockSize> {};
    if (!_queue.try_dequeue(block)) { return; }

    auto start = static_cast<std::size_t>(_numSamplesDequeued);
    for (auto i { 0U }; i < block.size(); ++i) {
        if (_numSamplesDequeued == _fft.getSize()) {
            runTransform();
            _numSamplesDequeued = 0;
            start               = 0U;
        }
        _monoBuffer[start + i] = block[i];
        ++_numSamplesDequeued;
    }
}

auto SpectrumSource::runTransform() -> void
{
    assert(_numSamplesDequeued == _fft.getSize());
    _windowing.multiplyWithWindowingTable(_monoBuffer.data(), (size_t)_monoBuffer.size());

    std::copy(_monoBuffer.begin(), _monoBuffer.end(), _fftBuffer.begin());
    _fft.performRealOnlyForwardTransform(data(_fftBuffer), true);

    auto const numBins       = static_cast<std::size_t>(_fft.getSize() / 2 + 1);
    auto const* coefficients = reinterpret_cast<juce::dsp::Complex<float> const*>(data(_fftBuffer));
    auto const bins          = Span<Complex<float> const> { coefficients, numBins };
    auto amplitudes          = Vector<float>(numBins, 0.0F);
    for (std::size_t i { 0 }; i < numBins; ++i) { amplitudes[i] = std::abs(bins[i]) / static_cast<float>(numBins); }

    {
        auto const lock = std::unique_lock { _renderMutex };
        _averager.push(amplitudes);
    }

    sendChangeMessage();
}

} // namespace mc
