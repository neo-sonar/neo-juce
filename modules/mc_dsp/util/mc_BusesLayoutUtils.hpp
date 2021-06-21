#ifndef MODERN_CIRCUITS_JUCE_MODULES_BUSES_LAYOUT_UTILS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_BUSES_LAYOUT_UTILS_HPP

namespace mc
{

struct BusesLayoutUtils
{
    /**
     * @brief Returns true if the given layout contains a main bus
     * configuration with the input & output having the same channel count.
     */
    [[nodiscard]] static auto isSameInOut(juce::AudioProcessor::BusesLayout const& layout) noexcept -> bool;

    /**
     * @brief Returns true if the given layout contains a main bus
     * configuration with the input & output both being stereo.
     */
    [[nodiscard]] static auto isStereoInOut(juce::AudioProcessor::BusesLayout const& layout) noexcept -> bool;
};

}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_BUSES_LAYOUT_UTILS_HPP
