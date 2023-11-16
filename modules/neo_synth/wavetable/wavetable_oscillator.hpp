#pragma once

namespace neo {

template <typename T>
struct WavetableOscillator {
    WavetableOscillator() = default;

    auto load(typename Wavetable<T>::Ptr wavetable) -> void;

    auto frequency(T newFrequency) -> void;
    auto morph(T newMorph) -> void;
    auto prepare(double sampleRate) -> void;
    auto processSample() -> T;
    auto reset(T phase) -> void;

private:
    typename Wavetable<T>::Ptr _wavetable { nullptr };
    T _phase { 0 };
    T _deltaPhase { 0 };
    T _sampleRate {};
    T _frequency { 440 };
    T _morph { 0 };
};

} // namespace neo

#include "wavetable_oscillator.cpp" // NOLINT(bugprone-suspicious-include)
