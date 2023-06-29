
namespace mc {

template <typename T>
constexpr auto unisonDetuneForVoiceUnsafe(int voices, int index) noexcept -> T
{
    auto offset = -1;
    auto bias   = T(2) / T(voices - 1);
    return bias * static_cast<T>(index) + static_cast<T>(offset);
}

template <typename T>
constexpr auto unisonDetuneForVoice(int voices, int index) noexcept -> T
{
    if (voices != 1) { return unisonDetuneForVoiceUnsafe<T>(voices, index); }
    return T(1) * static_cast<T>(index);
}

template <typename T>
UnisonOscillator<T>::UnisonOscillator() : _wavetable { makeSineWavetable<T>(2048) }
{
    _oscs.reserve(6);
    unison(1);
}

template <typename T>
auto UnisonOscillator<T>::load(typename Wavetable<T>::Ptr wavetable) -> void
{
    _wavetable = std::move(wavetable);
    for (auto& osc : _oscs) { osc.load(_wavetable); }
}

template <typename T>
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

template <typename T>
auto UnisonOscillator<T>::detune(T detuneInCents) -> void
{
    _detune = detuneInCents;
    for (auto i { 0 }; i < static_cast<int>(_oscs.size()); ++i) {
        auto const cents = _detune * unisonDetuneForVoice<T>(static_cast<int>(size(_oscs)), i);
        _oscs[(size_t)i].frequency(hertzWithCentsOffset(_frequency, cents));
    }
}

template <typename T>
auto UnisonOscillator<T>::morph(T newMorph) -> void
{
    for (auto& osc : _oscs) { osc.morph(newMorph); }
}

template <typename T>
auto UnisonOscillator<T>::prepare(double sampleRate) -> void
{
    _sampleRate = static_cast<T>(sampleRate);
    for (auto& osc : _oscs) { osc.prepare(sampleRate); }
    frequency(_frequency);
}

template <typename T>
auto UnisonOscillator<T>::process(juce::AudioBuffer<T>& buffer) -> void
{
    auto const numSamples  = buffer.getNumSamples();
    auto const numChannels = buffer.getNumChannels();

    for (auto& osc : _oscs) {
        for (auto i { 0 }; i < numSamples; ++i) {
            auto const sample = osc.processSample();
            for (auto ch { 0 }; ch < numChannels; ++ch) { buffer.addSample(ch, i, sample); }
        }
    }
}

template <typename T>
auto UnisonOscillator<T>::processSample() -> T
{
    T sample = 0;
    for (auto& osc : _oscs) { sample += osc.processSample(); }
    return sample * _gainCompensation;
}

template <typename T>
auto UnisonOscillator<T>::reset(T phaseIn) -> void
{
    for (auto& osc : _oscs) { osc.reset(phaseIn >= 0 ? phaseIn : static_cast<T>(_rndm.nextFloat())); }
}

template <typename T>
auto UnisonOscillator<T>::frequency(T newFrequency) -> void
{
    _frequency = newFrequency;
    // for (auto& osc : _oscs) { osc.frequency(_frequency); }
    detune(_detune);
}

// template <typename T, size_t MaxNumOscillators>
// UnisonWavetableOsc<T, MaxNumOscillators>::UnisonWavetableOsc() : _wavetable { makeSineWavetable<T>(2048) }
// {
//     unison(1);
// }

// template <typename T, size_t MaxNumOscillators>
// auto UnisonWavetableOsc<T, MaxNumOscillators>::load(typename Wavetable<T>::Ptr wavetable) -> void
// {
//     _wavetable = std::move(wavetable);
// }

// template <typename T, size_t MaxNumOscillators>
// auto UnisonWavetableOsc<T, MaxNumOscillators>::frequency(T newFrequency) -> void
// {
//     _frequency = newFrequency;
//     detune(_detune);
// }

// template <typename T, size_t MaxNumOscillators>
// auto UnisonWavetableOsc<T, MaxNumOscillators>::unison(int numOscillators) -> void
// {
//     _numOscillators = numOscillators;
//     detune(_detune);

//     // improvisiert, aber funktioniert
//     auto const gain = 1 / ((static_cast<T>(numOscillators - 1) * T(0.1)) + 1);
//     for (size_t i { 0 }; i < size(_gainCompensation); ++i) {
//         auto gains = std::array<T, xsimd::batch<T>::size> {};
//         for (auto& g : gains) { g = static_cast<int>(i) < numOscillators ? gain : T {}; }
//         _gainCompensation[i] = xsimd::batch<T>::load_unaligned(data(gains));
//     }
// }

// template <typename T, size_t MaxNumOscillators>
// auto UnisonWavetableOsc<T, MaxNumOscillators>::detune(T detuneInCents) -> void
// {
//     _detune = detuneInCents;

//     auto frequencies = std::array<T, maxNumOscillators> {};
//     for (auto i { 0 }; i < _numOscillators; ++i) {
//         auto const cents         = _detune * unisonDetuneForVoice<T>(_numOscillators, i);
//         frequencies[(size_t)(i)] = hertzWithCentsOffset(_frequency, cents);
//     }

//     for (size_t i { 0 }; i < size(_deltaPhase); ++i) {
//         auto const* ptr = data(frequencies) + i * xsimd::batch<T>::size;
//         _deltaPhase[i]  = xsimd::batch<T>::load_unaligned(ptr) / _sampleRate;
//     }
// }

// template <typename T, size_t MaxNumOscillators>
// auto UnisonWavetableOsc<T, MaxNumOscillators>::prepare(double sampleRate) -> void
// {
//     _sampleRate = static_cast<T>(sampleRate);
//     frequency(_frequency);
// }

// #if JUCE_MSVC && JUCE_DEBUG
//     #pragma optimize("t", on)
// #endif

// template <typename T, size_t MaxNumOscillators>
// auto UnisonWavetableOsc<T, MaxNumOscillators>::processSample() -> T
// {
//     auto sum = T {};

//     for (size_t i { 0 }; i < size(_deltaPhase); ++i) {
//         _phase[i] += _deltaPhase[i];
//         _phase[i] -= xsimd::floor(_phase[i]);

//         auto const scaledPhase  = _phase[i] * static_cast<T>(_wavetable->period());
//         auto const sampleIndex  = xsimd::to_int(scaledPhase);
//         auto const sampleOffset = scaledPhase - xsimd::to_float(sampleIndex);

//         auto const table   = Span<T const> { *_wavetable }.subspan(0, _wavetable->period());
//         auto const samples = samplesForHermiteInterpolation<T>(table, sampleIndex);
//         auto const sample  = HermiteInterpolation<xsimd::batch<T>> {}(samples, sampleOffset);

//         sum += xsimd::reduce_add(sample * _gainCompensation[i]);
//     }
//     return sum;
// }

// #if JUCE_MSVC && JUCE_DEBUG
//     #pragma optimize("", on)
// #endif

// template <typename T, size_t MaxNumOscillators>
// auto UnisonWavetableOsc<T, MaxNumOscillators>::reset(T phaseIn) -> void
// {
//     for (auto& phase : _phase) { phase = phaseIn; }
// }

} // namespace mc
