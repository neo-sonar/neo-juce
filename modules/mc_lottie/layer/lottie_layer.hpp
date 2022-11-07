#pragma once

namespace mc {

struct LottieLayer {
    [[nodiscard]] auto name() const -> String;
    [[nodiscard]] auto inOutPoints() const -> Optional<LottieInOutPoints>;
    [[nodiscard]] auto transform() const -> Optional<LottieTransform>;

    entt::registry& registry;
    entt::entity id;
    Vector<LottieShape> shapes;
};

} // namespace mc
