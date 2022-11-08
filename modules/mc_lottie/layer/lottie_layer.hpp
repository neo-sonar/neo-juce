#pragma once

namespace mc {

struct LottieLayer {
    [[nodiscard]] static auto parse(entt::registry& reg, juce::var const& obj) -> LottieLayer;

    [[nodiscard]] auto name() const -> String;
    [[nodiscard]] auto inOutPoints() const -> Optional<LottieInOutPoints>;
    [[nodiscard]] auto transform() const -> Optional<LottieTransform>;

    entt::registry& registry;
    entt::entity id;
};

inline auto parseLottieCommon(entt::registry& reg, entt::entity entity, juce::var const& obj)
{
    if (auto n = tryParseLottieName(obj); n) { reg.emplace<LottieName>(entity, std::move(*n)); }
    if (auto const p = tryParseLottieInOutPoints(obj); p) { reg.emplace<LottieInOutPoints>(entity, *p); }
    if (auto const t = tryParseLottieTransform(obj); t) { reg.emplace<LottieTransform>(entity, *t); }
}

inline auto checkLayerType(juce::var const& obj, LottieLayerType expected) -> void
{
    auto const& ty = obj["ty"];
    if (ty.isUndefined()) { raise<InvalidArgument>("no layer type"); }

    auto const type = static_cast<LottieLayerType>(static_cast<int>(ty));
    if (type != expected) { raise<InvalidArgument>("no layer type"); }
}

} // namespace mc
