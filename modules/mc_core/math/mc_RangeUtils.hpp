#ifndef MODERN_CIRCUITS_JUCE_MODULES_RANGE_UTILS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_RANGE_UTILS_HPP

namespace mc {
/**
 * @brief Collection of preconfigured ranges.
 */
class RangeUtils {
public:
    /**
     * @brief Deleted constructor. Static class.
     */
    RangeUtils() = delete;

    /**
     * @brief Returns a normalized range.
     */
    static auto defaultNormalizedRange() noexcept -> juce::NormalisableRange<float>
    {
        auto range = juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f };
        return range;
    }

    /**
     * @brief Returns a range for gain parameters.
     */
    static auto defaultGainRange() noexcept -> juce::NormalisableRange<float>
    {
        auto range = juce::NormalisableRange<float> { 0.0f, 4.0f, 0.01f };
        range.setSkewForCentre(1.0f);
        return range;
    }

    /**
     * @brief Returns a range for full range frequency parameters.
     */
    static auto defaultFrequencyRange() noexcept -> juce::NormalisableRange<float>
    {
        auto range = juce::NormalisableRange<float> { 20.0f, 22'000.0f, 1.0f };
        range.setSkewForCentre(3'000.0f);
        return range;
    }

    static auto defaultTimeRange() noexcept -> juce::NormalisableRange<float>
    {
        auto range = juce::NormalisableRange<float> { 0.0f, 2000.0f, 0.1f };
        range.setSkewForCentre(100.f);
        return range;
    }
};

} // namespace mc

template <typename ValueType>
struct juce::VariantConverter<juce::Range<ValueType>> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Range<ValueType>
    {
        auto const splits = mc::StringUtils::split(v.toString(), ':');
        auto const start  = mc::StringUtils::toValue<ValueType>(splits[0]);
        auto const end    = mc::StringUtils::toValue<ValueType>(splits[1]);
        return juce::Range<ValueType> { start, end };
    }

    [[nodiscard]] static auto toVar(juce::Range<ValueType> const& r) -> juce::var
    {
        return juce::String { fmt::format("{}:{}", r.getStart(), r.getEnd()) };
    }
};

template <typename ValueType>
struct juce::VariantConverter<juce::NormalisableRange<ValueType>> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::NormalisableRange<ValueType>
    {
        auto const splits        = mc::StringUtils::split(v.toString(), ':');
        auto const start         = mc::StringUtils::toValue<ValueType>(splits[0]);
        auto const end           = mc::StringUtils::toValue<ValueType>(splits[1]);
        auto const interval      = mc::StringUtils::toValue<ValueType>(splits[2]);
        auto const skew          = mc::StringUtils::toValue<ValueType>(splits[3]);
        auto const symmetricSkew = static_cast<int>(mc::StringUtils::toValue<ValueType>(splits[4])) == 1;
        return juce::NormalisableRange<ValueType> { start, end, interval, skew, symmetricSkew };
    }

    [[nodiscard]] static auto toVar(juce::NormalisableRange<ValueType> const& nr) -> juce::var
    {
        return juce::String { fmt::format("{}:{}:{}:{}:{}", nr.start, nr.end, nr.interval, nr.skew, nr.symmetricSkew) };
    }
};

#endif // MODERN_CIRCUITS_JUCE_MODULES_RANGE_UTILS_HPP
