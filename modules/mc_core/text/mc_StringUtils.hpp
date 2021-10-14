#ifndef MODERN_CIRCUITS_JUCE_MODULES_STRING_UTILS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_STRING_UTILS_HPP

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

struct StringUtils {
    MC_NODISCARD static auto split(juce::String const& str, char delimiter) -> std::vector<juce::String>
    {
        std::vector<juce::String> tokens {};
        std::string token {};
        std::istringstream tokenStream(str.toStdString());
        while (std::getline(tokenStream, token, delimiter)) { tokens.emplace_back(token); }
        return tokens;
    }

    template <typename ValueType>
    MC_NODISCARD static auto toValue(juce::String const& str) -> ValueType
    {
        return detail::ToValueImpl<ValueType> {}(str);
    }
};

} // namespace mc

#endif // MODERN_CIRCUITS_JUCE_MODULES_STRING_UTILS_HPP
