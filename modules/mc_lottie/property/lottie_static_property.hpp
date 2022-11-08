#pragma once

namespace mc {

template <typename PropertyType>
struct LottieStaticProperty {
    using Type = PropertyType;

    [[nodiscard]] static auto parse(juce::var const& obj) -> LottieStaticProperty;

    PropertyType value;
};

using StaticLottieColor = LottieStaticProperty<LottieColor>;

} // namespace mc

#include "lottie_static_property.ipp"
