#pragma once

namespace mc {

[[nodiscard]] inline auto parseDouble(juce::var const& obj) -> double { return static_cast<double>(obj); }

[[nodiscard]] inline auto parseOptionalDouble(juce::var const& obj, char const* token) -> Optional<double>
{
    if (auto const& val = obj[token]; not val.isUndefined()) { return parseDouble(val); }
    return {};
}

} // namespace mc
