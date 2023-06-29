namespace mc {
template <typename T>
auto WavetableOscillator<T>::load(typename Wavetable<T>::Ptr wavetable) -> void
{
    _wavetable = std::move(wavetable);
}

template <typename T>
auto WavetableOscillator<T>::frequency(T newFrequency) -> void
{
    _frequency  = newFrequency;
    _deltaPhase = newFrequency / _sampleRate;
}

template <typename T>
auto WavetableOscillator<T>::morph(T newMorph) -> void
{
    _morph = newMorph;
}

template <typename T>
auto WavetableOscillator<T>::prepare(double sampleRate) -> void
{
    _sampleRate = static_cast<T>(sampleRate);
    frequency(_frequency);
}

template <typename T>
auto WavetableOscillator<T>::processSample() -> T
{
    if (_wavetable == nullptr) { return 0; }
    if (_wavetable->empty()) { return 0; }

    _phase += _deltaPhase;
    _phase -= std::floor(_phase);

    auto const scaledPhase  = _phase * static_cast<T>(_wavetable->period());
    auto const sampleIndex  = static_cast<size_t>(scaledPhase);
    auto const sampleOffset = scaledPhase - static_cast<T>(sampleIndex);

    // auto const table   = morphed(*_wavetable, std::clamp(_morph, T(0), T(1)));
    auto const table   = std::span<T const> { *_wavetable }.subspan(0, _wavetable->period());
    auto const samples = samplesForHermiteInterpolation<T>(table, sampleIndex);
    // auto const samples = std::array<T, 4> {
    //     table[sampleIndex - 1U],
    //     table[sampleIndex],
    //     table[sampleIndex + 1U],
    //     table[sampleIndex + 2U],
    // };
    return HermiteInterpolation<T> {}(samples, sampleOffset);
}

template <typename T>
auto WavetableOscillator<T>::reset(T phase) -> void
{
    _phase = phase;
}
} // namespace mc
