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

template <typename T, size_t MaxNumOscillators>
struct UnisonOscillatorV2 {
    using SampleType                        = T;
    static constexpr auto maxNumOscillators = MaxNumOscillators;

    UnisonOscillatorV2() : _wavetable { makeSineWavetable<T>(2048) } { unison(1); }

    auto load(typename Wavetable<T>::Ptr wavetable) -> void { _wavetable = std::move(wavetable); }

    auto frequency(T newFrequency) -> void
    {
        _frequency = newFrequency;
        detune(_detune);
    }

    auto unison(int numOscillators) -> void
    {
        _numOscillators = numOscillators;
        detune(_detune);

        // improvisiert, aber funktioniert
        auto const gain = 1 / ((static_cast<T>(numOscillators - 1) * T(0.1)) + 1);
        for (size_t i { 0 }; i < size(_gainCompensation); ++i) {
            auto gains = Array<T, xsimd::batch<T>::size> {};
            for (auto& g : gains) { g = static_cast<int>(i) < numOscillators ? gain : T {}; }
            _gainCompensation[i] = xsimd::batch<T>::load_unaligned(data(gains));
        }
    }

    auto detune(T detuneInCents) -> void
    {
        _detune = detuneInCents;

        auto frequencies = Array<T, maxNumOscillators> {};
        for (auto i { 0 }; i < _numOscillators; ++i) {
            auto const cents         = _detune * unisonDetuneForVoice<T>(_numOscillators, i);
            frequencies[(size_t)(i)] = hertzWithCentsOffset(_frequency, cents);
        }

        for (size_t i { 0 }; i < size(_deltaPhase); ++i) {
            auto const* ptr = data(frequencies) + i * xsimd::batch<T>::size;
            _deltaPhase[i]  = xsimd::batch<T>::load_unaligned(ptr) / _sampleRate;
        }
    }

    auto morph(T) -> void { }

    auto prepare(double sampleRate) -> void
    {
        _sampleRate = static_cast<T>(sampleRate);
        frequency(_frequency);
    }

    auto processSample() -> T
    {
        auto sum = T {};
        for (size_t i { 0 }; i < size(_deltaPhase); ++i) {
            _phase[i] += _deltaPhase[i];
            _phase[i] -= xsimd::floor(_phase[i]);

            auto const scaledPhase  = _phase[i] * static_cast<T>(_wavetable->period());
            auto const sampleIndex  = xsimd::to_int(scaledPhase);
            auto const sampleOffset = scaledPhase - xsimd::to_float(sampleIndex);

            auto const table   = Span<T const> { *_wavetable }.subspan(0, _wavetable->period());
            auto const samples = mc::Array<xsimd::batch<T>, 4> {
                xsimd::batch<T>::gather(data(table), sampleIndex - 1),
                xsimd::batch<T>::gather(data(table), sampleIndex + 0),
                xsimd::batch<T>::gather(data(table), sampleIndex + 1),
                xsimd::batch<T>::gather(data(table), sampleIndex + 2),
            };

            auto ip = HermiteInterpolation<xsimd::batch<T>> {};
            sum += xsimd::reduce_add(ip(samples, sampleOffset) * _gainCompensation[i]);
        }
        return sum;
    }

    // /// \brief if phaseIn is below 0, the phases will be random.
    auto reset(T phaseIn = 0) -> void
    {
        for (auto& phase : _phase) { phase = phaseIn; }
    }

private:
    // static_assert(maxNumOscillators % xsimd::batch<T>::size == 0);
    static constexpr auto numBatches = std::max<size_t>(1, maxNumOscillators / xsimd::batch<T>::size);

    typename Wavetable<T>::Ptr _wavetable;

    int _numOscillators { 0 };

    Array<xsimd::batch<T>, numBatches> _phase {};
    Array<xsimd::batch<T>, numBatches> _deltaPhase {};
    Array<xsimd::batch<T>, numBatches> _gainCompensation {};

    T _sampleRate { 44'100.0 };
    T _frequency { 440 };
    T _detune { 0 };
};

} // namespace mc

#include "unison_oscillator.ipp"
