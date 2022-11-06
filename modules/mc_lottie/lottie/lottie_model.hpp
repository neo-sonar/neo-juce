#pragma once

namespace mc {

enum struct LottieBlendMode {
    normal     = 0,
    multiply   = 1,
    screen     = 2,
    overlay    = 3,
    darken     = 4,
    lighten    = 5,
    colorDodge = 6,
    colorBurn  = 7,
    hardLight  = 8,
    softLight  = 9,
    difference = 10,
    exclusion  = 11,
    hue        = 12,
    saturation = 13,
    color      = 14,
    luminosity = 15,
    add        = 16,
    hardMix    = 17,
};

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

struct LottieTransform { };

struct LottieNullLayer {
    inline static constexpr auto type = LottieLayerType::null;

    LottieTransform transform {};
    double inPoint { 0 };
    double outPoint { 0 };

    Optional<String> name {};
    Optional<bool> is3D { false };
};

struct LottieShapeLayer {
    inline static constexpr auto type = LottieLayerType::shape;

    double inPoint { 0 };
    double outPoint { 0 };

    Optional<String> name {};
    Optional<bool> is3D { false };
};

using LottieLayer = variant<LottieNullLayer, LottieShapeLayer>;

struct LottieModel {
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

[[nodiscard]] auto loadLottieModel(juce::File const& path) -> Expected<LottieModel, String>;
[[nodiscard]] auto parseLottieModel(juce::var const& model) -> Expected<LottieModel, String>;

[[nodiscard]] auto parseLottieLayer(juce::var const& layer) -> Expected<LottieLayer, String>;
[[nodiscard]] auto parseLottieNullLayer(juce::var const& layer) -> Expected<LottieNullLayer, String>;
[[nodiscard]] auto parseLottieShapeLayer(juce::var const& layer) -> Expected<LottieShapeLayer, String>;

} // namespace mc
