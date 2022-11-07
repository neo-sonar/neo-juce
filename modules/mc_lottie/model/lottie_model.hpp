#pragma once

namespace mc {

struct LottieLayer2 {
    [[nodiscard]] auto name() const -> String;
    [[nodiscard]] auto inOutPoints() const -> Optional<LottieInOutPoints>;
    [[nodiscard]] auto transform() const -> Optional<LottieTransform>;

    entt::registry& registry;
    entt::entity id;
};

struct LottieModel {
    explicit LottieModel(juce::File const& file);

    [[nodiscard]] auto name() const -> String const&;
    [[nodiscard]] auto version() const -> String const&;
    [[nodiscard]] auto inPoint() const -> double;
    [[nodiscard]] auto outPoint() const -> double;
    [[nodiscard]] auto width() const -> double;
    [[nodiscard]] auto height() const -> double;
    [[nodiscard]] auto framerate() const -> double;
    [[nodiscard]] auto layers() const -> Vector<LottieLayer2> const&;

private:
    entt::registry _registry;
    entt::entity _root;
    Vector<LottieLayer2> _layers;
};

} // namespace mc
