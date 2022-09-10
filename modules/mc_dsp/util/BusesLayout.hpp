#pragma once

namespace mc {

/// \brief Returns true if the given layout contains a main bus
/// configuration with the input & output having the same channel count.
MC_NODISCARD auto isSameInOut(juce::AudioProcessor::BusesLayout const& layout) noexcept -> bool;

/// \brief Returns true if the given layout contains a main bus
/// configuration with the input & output both being mono.
MC_NODISCARD auto isMonoInOut(juce::AudioProcessor::BusesLayout const& layout) noexcept -> bool;

/// \brief Returns true if the given layout contains a main bus
/// configuration with the input & output both being stereo.
MC_NODISCARD auto isStereoInOut(juce::AudioProcessor::BusesLayout const& layout) noexcept -> bool;

} // namespace mc
