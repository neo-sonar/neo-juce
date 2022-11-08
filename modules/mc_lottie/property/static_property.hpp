#pragma once

namespace mc {
template <typename PropertyType>
struct StaticProperty {
    using Type = PropertyType;

    [[nodiscard]] static auto parse(juce::var const& obj) -> StaticProperty
    {
        auto const& property = obj["c"];
        if (property.isUndefined()) { raise<InvalidArgument>("missing property"); }

        auto const animated = static_cast<int>(property["a"]) == 1;
        if (animated) { raise<InvalidArgument>("animated, but parsing static"); }

        return { PropertyType::parse(property["k"]) };
    }

    PropertyType value;
};

using StaticLottieColor = StaticProperty<LottieColor>;

} // namespace mc