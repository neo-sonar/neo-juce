#pragma once

namespace mc {

enum struct LottieLayerType {
    precomposition   = 0,
    solidColor       = 1,
    image            = 2,
    null             = 3,
    shape            = 4,
    text             = 5,
    audio            = 6,
    videoPlaceholder = 7,
    imageSequence    = 8,
    video            = 9,
    imagePlaceholder = 10,
    guide            = 11,
    adjustment       = 12,
    camera           = 13,
    light            = 14,
    data             = 15,
};

struct LottieNullLayer { };

struct LottieShapeLayer {
    int ip { 0 };
    int op { 0 };
};

using LottieLayer = variant<LottieNullLayer, LottieShapeLayer>;

struct LottieModel {
    String name {};
    String version {};
    int ip { 0 };
    int op { 0 };
    int framerate { 60 };
    int width { 512 };
    int height { 512 };
    int ddd { false };
    Vector<LottieLayer> layers;
};

[[nodiscard]] auto loadLottieModel(juce::File const& path) -> Expected<LottieModel, String>;
[[nodiscard]] auto parseLottieModel(juce::var const& model) -> Expected<LottieModel, String>;

[[nodiscard]] auto parseLottieLayer(juce::var const& layer) -> Expected<LottieLayer, String>;
[[nodiscard]] auto parseLottieNullLayer(juce::var const& layer) -> Expected<LottieNullLayer, String>;
[[nodiscard]] auto parseLottieShapeLayer(juce::var const& layer) -> Expected<LottieShapeLayer, String>;

} // namespace mc
