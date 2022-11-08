#pragma once

namespace mc {

struct LottieLayerNull {
    static auto parse(entt::registry& reg, juce::var const& obj) -> LottieLayer;
};

} // namespace mc
