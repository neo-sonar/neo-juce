#ifndef MODERN_CIRCUITS_JUCE_MODULES_CONSTANTS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_CONSTANTS_HPP

namespace mc
{
/**
 * @brief Euler constant.
 */
template<typename Type>
inline constexpr auto Euler = Type {2.71828182845904523536};

/**
 * @brief Pi constant.
 */
template<typename Type>
inline constexpr auto Pi = Type {3.14159265358979323846};

}  // namespace mc
#endif  // MODERN_CIRCUITS_JUCE_MODULES_CONSTANTS_HPP
