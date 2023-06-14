// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace mc::strings {
inline auto split(juce::String const& str, char delimiter) -> std::vector<juce::String>
{
    std::vector<juce::String> tokens {};
    std::string token {};
    std::istringstream tokenStream(str.toStdString());
    while (std::getline(tokenStream, token, delimiter)) { tokens.emplace_back(token); }
    return tokens;
}

template <typename T>
auto toValue(juce::String const& str) -> T
{
    if constexpr (std::is_same_v<T, int>) {
        return str.getIntValue();
    } else if (std::is_same_v<T, float>) {
        return str.getFloatValue();
    } else {
        return static_cast<T>(str.getDoubleValue());
    }
}
} // namespace mc::strings
