#pragma once

namespace mc {

namespace detail {
template <typename T>
struct ToValueImpl {
    auto operator()(juce::String const& str) -> T { return static_cast<T>(str.getDoubleValue()); }
};

template <>
struct ToValueImpl<int> {
    auto operator()(juce::String const& str) -> int { return str.getIntValue(); }
};
template <>
struct ToValueImpl<float> {
    auto operator()(juce::String const& str) -> float { return str.getFloatValue(); }
};
} // namespace detail

namespace strings {
MC_NODISCARD inline auto split(juce::String const& str, char delimiter) -> Vector<juce::String>
{
    Vector<juce::String> tokens {};
    std::string token {};
    std::istringstream tokenStream(str.toStdString());
    while (std::getline(tokenStream, token, delimiter)) { tokens.emplace_back(token); }
    return tokens;
}

template <typename ValueType>
MC_NODISCARD inline auto toValue(juce::String const& str) -> ValueType
{
    return detail::ToValueImpl<ValueType> {}(str);
}
} // namespace strings

} // namespace mc
