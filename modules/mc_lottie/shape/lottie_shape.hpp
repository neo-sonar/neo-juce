#pragma once

namespace mc {

struct LottieShape {
    [[nodiscard]] static auto parse(entt::registry& reg, juce::var const& obj) -> LottieShape;

    [[nodiscard]] auto name() const -> String;
    [[nodiscard]] auto type() const -> LottieShapeType;

    entt::registry& registry;
    entt::entity id;
};

} // namespace mc
