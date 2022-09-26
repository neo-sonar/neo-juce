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

SpectrumSource::SpectrumSource(int fftOrder)
    : _fft(fftOrder)
    , _windowing { size_t(_fft.getSize()), juce::dsp::WindowingFunction<float>::hann, true }
    , _queue { 64 }
{
    _monoBuffer.setSize(1, _fft.getSize());
    _fftBuffer.resize(_fft.getSize() * 2U);
    jassert(_fftBuffer.size() == _fft.getSize() * 2U);
}

SpectrumSource::~SpectrumSource() { reset(); }

auto SpectrumSource::prepare(juce::dsp::ProcessSpec const& spec) -> void
{
    _spec = spec;
    reset();
    _shouldExit.store(false);
    _thread = makeUnique<std::thread>([this] { backgroundThread(); });
}

auto SpectrumSource::reset() -> void
{
    if (_thread == nullptr) { return; }
    _shouldExit.store(true);
    if (_thread->joinable()) { _thread->join(); }
    _thread.reset(nullptr);
}

auto SpectrumSource::makePath(juce::Rectangle<float> bounds) -> juce::Path
{
    auto const lock = std::unique_lock { _renderMutex };

    auto const numBins       = static_cast<std::size_t>(_fft.getSize() / 2 + 1);
    auto const* coefficients = reinterpret_cast<juce::dsp::Complex<float> const*>(data(_fftBuffer));
    auto const bins          = Span<Complex<float> const> { coefficients, numBins };

    auto const minFrequency = 20.0F;
    auto const maxFrequency = static_cast<float>(_spec.sampleRate) / 2.0F;

    auto const size = static_cast<int>(bins.size());
    if (size == 0) return {};

    auto p = juce::Path {};
    p.preallocateSpace(8 + size * 3);

    auto i { 0U };
    while (frequencyForBin<float>(_fft.getSize(), i, _spec.sampleRate) < minFrequency) { ++i; }

    auto const width  = bounds.getWidth();
    auto const freq   = frequencyForBin<float>(_fft.getSize(), i, _spec.sampleRate);
    auto const startY = amplitudeToY(std::abs(bins[i]) / static_cast<float>(size), bounds);
    auto const startX = frequencyToX(minFrequency, maxFrequency, freq, width);
    p.startNewSubPath(bounds.getX() + startX, startY);

    for (; i < bins.size(); ++i) {
        auto const frequency = frequencyForBin<float>(_fft.getSize(), i, _spec.sampleRate);
        auto const amplitude = std::abs(bins[i]) / static_cast<float>(size);
        auto const y         = amplitudeToY(amplitude, bounds);
        p.lineTo(bounds.getX() + frequencyToX(minFrequency, maxFrequency, frequency, width), y);
    }

    return p;
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

auto SpectrumSource::backgroundThread() -> void
{
    while (!_shouldExit.load()) {
        auto block = StaticVector<float, maxSubBlockSize> {};
        if (!_queue.try_dequeue(block)) { continue; }

        auto start = _numSamplesDequeued;
        for (auto i { 0 }; i < block.size(); ++i) {
            if (_numSamplesDequeued == _fft.getSize()) {
                runTransform();
                _numSamplesDequeued = 0;
                start               = 0;
            }
            _monoBuffer.setSample(0, start + i, block[i]);
            ++_numSamplesDequeued;
        }
    }
}

auto SpectrumSource::runTransform() -> void
{
    assert(_numSamplesDequeued == _fft.getSize());
    _windowing.multiplyWithWindowingTable(_monoBuffer.getWritePointer(0), (size_t)_monoBuffer.getNumSamples());

    auto const lock = std::unique_lock { _renderMutex };
    {
        std::copy(_monoBuffer.getReadPointer(0), _monoBuffer.getReadPointer(0) + _fft.getSize(), _fftBuffer.begin());
        _fft.performRealOnlyForwardTransform(data(_fftBuffer), true);
    }

    sendChangeMessage();
}

} // namespace mc
