#pragma once

namespace mc {

struct LottieLayerShape {
    static auto parse(entt::registry& reg, juce::var const& obj) -> LottieLayer;

    Vector<LottieShape> shapes;
};

} // namespace mc
