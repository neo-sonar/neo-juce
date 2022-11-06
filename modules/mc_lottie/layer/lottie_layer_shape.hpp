#pragma once

namespace mc {

struct LottieShapeLayer {
    inline static constexpr auto type = LottieLayerType::shape;

    LottieTransform transform {};
    double inPoint { 0 };
    double outPoint { 0 };

    Optional<String> name {};
    Optional<bool> is3D { false };
};

[[nodiscard]] auto parseLottieShapeLayer(juce::var const& obj) -> Expected<LottieShapeLayer, String>;

inline auto parseLottieShapeLayer(juce::var const& obj) -> Expected<LottieShapeLayer, String>
{
    auto layer = LottieShapeLayer {};
    parseLottieLayerCommon(obj, layer);

    auto transform = parseLottieTransform(obj["ks"]);
    if (not transform.has_value()) { return makeUnexpected("missing transform"); }
    layer.transform = *transform;

    return layer;
}

} // namespace mc
