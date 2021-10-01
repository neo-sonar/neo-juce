#ifndef MODERN_CIRCUITS_JUCE_MODULES_STRING_UTILS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_STRING_UTILS_HPP

namespace mc {

struct StringUtils {
    MC_NODISCARD static auto split(juce::String const& str, char delimiter) -> std::vector<juce::String>
    {
        std::vector<juce::String> tokens {};
        std::string token {};
        std::istringstream tokenStream(str.toStdString());
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.emplace_back(token);
        }
        return tokens;
    }

    template <typename ValueType>
    MC_NODISCARD static auto toValue(juce::String const& str) -> ValueType
    {
        if constexpr (std::is_same_v<ValueType, int>) {
            return str.getIntValue();
        }
        if constexpr (std::is_same_v<ValueType, float>) {
            return str.getFloatValue();
        }
        return static_cast<ValueType>(str.getDoubleValue());
    }
};

} // namespace mc

#endif // MODERN_CIRCUITS_JUCE_MODULES_STRING_UTILS_HPP
