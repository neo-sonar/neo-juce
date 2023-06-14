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

    std::vector<WavetableOscillator<T>> _oscs {};
    typename Wavetable<T>::Ptr _wavetable;
    juce::Random _rndm;
};

template <typename T>
[[nodiscard]] constexpr auto unisonDetuneForVoice(int voices, int index) noexcept -> T;

template <typename T>
[[nodiscard]] constexpr auto unisonDetuneForVoiceUnsafe(int voices, int index) noexcept -> T;

template <typename T, size_t MaxNumOscillators>
struct UnisonWavetableOsc {
    using SampleType                        = T;
    static constexpr auto maxNumOscillators = MaxNumOscillators;

    UnisonWavetableOsc();

    auto load(typename Wavetable<T>::Ptr wavetable) -> void;

    auto frequency(T newFrequency) -> void;
    auto unison(int numOscillators) -> void;
    auto detune(T detuneInCents) -> void;

    auto prepare(double sampleRate) -> void;
    auto processSample() -> T;
    auto reset(T phaseIn = 0) -> void;

private:
    static constexpr auto numBatches = std::max<size_t>(1, maxNumOscillators / xsimd::batch<T>::size);

    typename Wavetable<T>::Ptr _wavetable;

    int _numOscillators { 0 };

    std::array<xsimd::batch<T>, numBatches> _phase {};
    std::array<xsimd::batch<T>, numBatches> _deltaPhase {};
    std::array<xsimd::batch<T>, numBatches> _gainCompensation {};

    T _sampleRate { 44'100.0 };
    T _frequency { 440 };
    T _detune { 0 };
};

} // namespace mc

#include "unison_oscillator.ipp"
