#pragma once

namespace neo::fx {

/// \brief The DeRez effect from the AirWindows plugin collection. Adapted
/// to work with JUCE dsp chains.
///
/// Check the description for more details about the effect:
/// https://www.airwindows.com/wp-content/uploads/Airwindopedia.txt
///
/// The original code is licensed under the MIT-License:
/// https://github.com/airwindows/airwindows
template <typename T>
struct AirWindowsDeRez {
    struct Parameter {
        T rate { 1 };       // 0.0 <-> 1.0
        T resolution { 1 }; // 0.0 <-> 1.0
    };

    AirWindowsDeRez() = default;

    auto parameter(Parameter const& param) -> void;

    /// \brief Initialises the process.
    auto prepare(juce::dsp::ProcessSpec const& spec) -> void;

    /// \brief Resets the process's internal state.
    auto reset() noexcept -> void;

    /// \brief Applies the process to an audio buffer.
    template <typename ProcessContext>
    auto process(ProcessContext const& context) noexcept -> void;

private:
    juce::dsp::ProcessSpec _spec {};

    T _targetA {};
    T _targetB {};
    T _soften {};

    T _incrementFrequency {};
    T _incrementBitDepth {};

    T _lastSample {};
    T _heldSample {};
    T _position {};
};

} // namespace neo::fx

#include "airwindows_derez.ipp"
