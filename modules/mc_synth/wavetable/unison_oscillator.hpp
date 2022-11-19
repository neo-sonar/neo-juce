#pragma once

namespace mc {

template <typename T>
struct UnisonOscillator {
    UnisonOscillator();

    auto load(typename Wavetable<T>::Ptr wavetable) -> void;

    auto frequency(T newFrequency) -> void;
    auto unison(int numOscillators) -> void;
    auto detune(T detuneInCents) -> void;

    auto morph(T newMorph) -> void;

    auto prepare(double sampleRate) -> void;
    auto process(juce::AudioBuffer<T>& buffer) -> void;
    auto processSample() -> T;

    /// \brief if phaseIn is below 0, the phases will be random.
    auto reset(T phaseIn = 0) -> void;

private:
    T _sampleRate {};

    T _frequency { 440 };
    T _detune { 0 };
    T _gainCompensation { 1 };

    Vector<WavetableOscillator<T>> _oscs {};
    typename Wavetable<T>::Ptr _wavetable;
    juce::Random _rndm;
};

template <typename T>
[[nodiscard]] constexpr auto unisonDetuneForVoice(int voices, int index) noexcept -> T;

template <typename T>
[[nodiscard]] constexpr auto unisonDetuneForVoiceUnsafe(int voices, int index) noexcept -> T;

} // namespace mc

#include "unison_oscillator.ipp"
