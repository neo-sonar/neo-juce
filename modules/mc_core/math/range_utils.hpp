#ifndef MODERN_CIRCUITS_JUCE_MODULES_RANGE_UTILS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_RANGE_UTILS_HPP

template<typename ValueType>
struct juce::VariantConverter<juce::Range<ValueType>>
{
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Range<ValueType>
    {
        auto const splits = mc::StringUtils::split(v.toString(), ':');
        auto const start  = mc::StringUtils::toValue<ValueType>(splits[0]);
        auto const end    = mc::StringUtils::toValue<ValueType>(splits[1]);
        return juce::Range<ValueType> {start, end};
    }

    [[nodiscard]] static auto toVar(juce::Range<ValueType> const& r) -> juce::var
    {
        return juce::String {fmt::format("{}:{}", r.getStart(), r.getEnd())};
    }
};

template<typename ValueType>
struct juce::VariantConverter<juce::NormalisableRange<ValueType>>
{
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::NormalisableRange<ValueType>
    {
        auto const splits        = mc::StringUtils::split(v.toString(), ':');
        auto const start         = mc::StringUtils::toValue<ValueType>(splits[0]);
        auto const end           = mc::StringUtils::toValue<ValueType>(splits[1]);
        auto const interval      = mc::StringUtils::toValue<ValueType>(splits[2]);
        auto const skew          = mc::StringUtils::toValue<ValueType>(splits[3]);
        auto const symmetricSkew = static_cast<int>(mc::StringUtils::toValue<ValueType>(splits[4])) == 1;
        return juce::NormalisableRange<ValueType> {start, end, interval, skew, symmetricSkew};
    }

    [[nodiscard]] static auto toVar(juce::NormalisableRange<ValueType> const& nr) -> juce::var
    {
        return juce::String {fmt::format("{}:{}:{}:{}:{}", nr.start, nr.end, nr.interval, nr.skew, nr.symmetricSkew)};
    }
};

#endif  // MODERN_CIRCUITS_JUCE_MODULES_RANGE_UTILS_HPP
