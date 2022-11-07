#pragma once

namespace mc {

struct LottieModel {
    explicit LottieModel(juce::File const& file);

    [[nodiscard]] auto name() const -> String const&;
    [[nodiscard]] auto version() const -> String const&;
    [[nodiscard]] auto inPoint() const -> double;
    [[nodiscard]] auto outPoint() const -> double;
    [[nodiscard]] auto width() const -> double;
    [[nodiscard]] auto height() const -> double;
    [[nodiscard]] auto framerate() const -> double;

private:
    entt::registry _registry;
    entt::entity _root;
};

} // namespace mc
