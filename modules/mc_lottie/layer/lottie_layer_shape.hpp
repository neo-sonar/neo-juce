#pragma once

namespace mc {

struct LottieShapeLayer {
    inline static constexpr auto type = LottieLayerType::shape;

    LottieTransform transform {};
    double inPoint { 0 };
    double outPoint { 0 };
    Vector<LottieShape> shapes {};

    Optional<String> name {};
    Optional<bool> is3D { false };
};

[[nodiscard]] auto parseLottieShapeLayer(juce::var const& obj) -> Expected<LottieShapeLayer, String>;

} // namespace mc
