#pragma once

namespace mc {

struct LottieAnimation {
    [[nodiscard]] static auto load(juce::File const& path) -> Expected<LottieAnimation, String>;
    [[nodiscard]] static auto parse(juce::var const& root) -> Expected<LottieAnimation, String>;

    double inPoint { 0 };
    double outPoint { 0 };
    double framerate { 0 };
    double width { 0 };
    double height { 0 };
    Vector<LottieLayer> layers;

    Optional<String> name {};
    Optional<String> version {};

    bool is3D { false };
};

} // namespace mc
