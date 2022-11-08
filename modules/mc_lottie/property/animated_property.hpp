#pragma once

namespace mc {

template <typename PropertyType>
struct AnimatedProperty {
    using Type = PropertyType;
    struct Keyframe {
        double frame;
        Type value;
    };

    [[nodiscard]] static auto parse(juce::var const& obj) -> AnimatedProperty
    {
        auto const& property = obj["c"];
        if (property.isUndefined()) { raise<InvalidArgument>("missing property"); }

        auto const animated = static_cast<int>(property["a"]) == 1;
        if (not animated) { raise<InvalidArgument>("static, but parsing animated"); }

        // PropertyType::parse(property["k"])
        return {};
    }

    Vector<Keyframe> keyframes;
};

using AnimatedLottieColor = AnimatedProperty<LottieColor>;

} // namespace mc