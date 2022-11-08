#pragma once

namespace mc {

template <typename PropertyType>
struct LottieAnimatedProperty {
    using Type = PropertyType;
    struct Keyframe {
        double frame;
        Type value;
    };

    [[nodiscard]] static auto parse(juce::var const& obj) -> LottieAnimatedProperty;

    Vector<Keyframe> keyframes;
};

using AnimatedLottieColor = LottieAnimatedProperty<LottieColor>;

} // namespace mc


#include "lottie_animated_property.ipp"