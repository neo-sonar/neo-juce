#pragma once

namespace mc {

struct LottieLayer2 {
    [[nodiscard]] auto name() const -> String;
    [[nodiscard]] auto inOutPoints() const -> Optional<LottieInOutPoints>;
    [[nodiscard]] auto transform() const -> Optional<LottieTransform>;

    entt::registry& registry;
    entt::entity id;
    Vector<LottieShape2> shapes;
};

} // namespace mc
