
namespace mc {

template<typename T>
constexpr auto unisonDetuneForVoiceUnsafe(int voices, int index) noexcept -> T
{
    auto offset = -1;
    auto bias   = T(2) / T(voices - 1);
    return bias * static_cast<T>(index) + static_cast<T>(offset);
}

template<typename T>
constexpr auto unisonDetuneForVoice(int voices, int index) noexcept -> T
{
    if (voices != 1) { return unisonDetuneForVoiceUnsafe<T>(voices, index); }
    return T(1) * static_cast<T>(index);
}

template<typename T>
UnisonOscillator<T>::UnisonOscillator()
    : _wavetable{makeSineWavetable<T>(2048)}
{
    _oscs.reserve(6);
    unison(1);
}

template<typename T>
auto UnisonOscillator<T>::load(typename Wavetable<T>::Ptr wavetable) -> void
{
    _wavetable = std::move(wavetable);
    for (auto& osc : _oscs) { osc.load(_wavetable); }
}

template<typename T>
auto UnisonOscillator<T>::unison(int numOscillators) -> void
{
    if (numOscillators == static_cast<int>(size(_oscs))) { return; }

    _oscs.clear();
    for (int i = 0; i < numOscillators; ++i) { _oscs.emplace_back(); }
    load(_wavetable);
    prepare(_sampleRate);

    // improvisiert, aber funktioniert
    _gainCompensation = 1 / ((static_cast<T>(numOscillators - 1) * T(0.1)) + 1);
}

template<typename T>
auto UnisonOscillator<T>::detune(T detuneInCents) -> void
{
    _detune = detuneInCents;
    for (auto i{0}; i < mc::ssize(_oscs); ++i) {
        auto const cents = _detune * unisonDetuneForVoice<T>(static_cast<int>(size(_oscs)), i);
        _oscs[(size_t)i].frequency(hertzWithCentsOffset(_frequency, cents));
    }
}

template<typename T>
auto UnisonOscillator<T>::morph(T newMorph) -> void
{
    for (auto& osc : _oscs) { osc.morph(newMorph); }
}

template<typename T>
auto UnisonOscillator<T>::prepare(double sampleRate) -> void
{
    _sampleRate = static_cast<T>(sampleRate);
    for (auto& osc : _oscs) { osc.prepare(sampleRate); }
    frequency(_frequency);
}

template<typename T>
auto UnisonOscillator<T>::process(juce::AudioBuffer<T>& buffer) -> void
{
    auto const numSamples  = buffer.getNumSamples();
    auto const numChannels = buffer.getNumChannels();

    for (auto& osc : _oscs) {
        for (auto i{0}; i < numSamples; ++i) {
            auto const sample = osc.processSample();
            for (auto ch{0}; ch < numChannels; ++ch) { buffer.addSample(ch, i, sample); }
        }
    }
}

template<typename T>
auto UnisonOscillator<T>::processSample() -> T
{
    T sample = 0;
    for (auto& osc : _oscs) { sample += osc.processSample(); }
    return sample * _gainCompensation;
}

template<typename T>
auto UnisonOscillator<T>::reset(T phaseIn) -> void
{
    for (auto& osc : _oscs) { osc.reset(phaseIn >= 0 ? phaseIn : static_cast<T>(_rndm.nextFloat())); }
}

template<typename T>
auto UnisonOscillator<T>::frequency(T newFrequency) -> void
{
    _frequency = newFrequency;
    // for (auto& osc : _oscs) { osc.frequency(_frequency); }
    detune(_detune);
}

}  // namespace mc
