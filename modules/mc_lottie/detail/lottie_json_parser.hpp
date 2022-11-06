#pragma once

namespace mc {

[[nodiscard]] inline auto parseBool(juce::var const& obj) -> bool { return static_cast<bool>(obj); }
[[nodiscard]] inline auto parseDouble(juce::var const& obj) -> double { return static_cast<double>(obj); }
[[nodiscard]] inline auto parseString(juce::var const& obj) -> String { return obj.toString().toStdString(); }

[[nodiscard]] inline auto parseBool(juce::var const& obj, char const* token) -> bool
{
    if (auto const& val = obj[token]; not val.isUndefined()) { return parseBool(val); }
    throw RuntimeError { "invalid type" };
}

[[nodiscard]] inline auto parseDouble(juce::var const& obj, char const* token) -> double
{
    if (auto const& val = obj[token]; not val.isUndefined()) { return parseDouble(val); }
    throw RuntimeError { "invalid type" };
}

[[nodiscard]] inline auto parseString(juce::var const& obj, char const* token) -> String
{
    if (auto const& val = obj[token]; not val.isUndefined()) { return parseString(val); }
    throw RuntimeError { "invalid type" };
}

[[nodiscard]] inline auto parseOptionalBool(juce::var const& obj, char const* token) -> Optional<bool>
{
    if (auto const& val = obj[token]; not val.isUndefined()) { return parseBool(val); }
    return {};
}

[[nodiscard]] inline auto parseOptionalDouble(juce::var const& obj, char const* token) -> Optional<double>
{
    if (auto const& val = obj[token]; not val.isUndefined()) { return parseDouble(val); }
    return {};
}

[[nodiscard]] inline auto parseOptionalString(juce::var const& obj, char const* token) -> Optional<String>
{
    if (auto const& val = obj[token]; not val.isUndefined()) { return parseString(val); }
    return {};
}

template <typename T>
static auto parseLottieLayerCommon(juce::var const& obj, T& layer)
{
    layer.inPoint  = parseDouble(obj, "ip");
    layer.outPoint = parseDouble(obj, "op");
    layer.name     = parseOptionalString(obj, "nm");
    layer.is3D     = parseOptionalBool(obj, "ddd").value_or(false);
}

} // namespace mc
