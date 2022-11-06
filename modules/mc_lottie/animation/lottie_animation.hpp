#pragma once

namespace mc {

struct LottieAnimation {
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

[[nodiscard]] auto loadLottieAnimation(juce::File const& path) -> Expected<LottieAnimation, String>;
[[nodiscard]] auto parseLottieAnimation(juce::var const& root) -> Expected<LottieAnimation, String>;

} // namespace mc
