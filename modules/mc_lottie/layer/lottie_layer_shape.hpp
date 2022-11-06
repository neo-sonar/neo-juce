#pragma once

namespace mc {

struct LottieShapeLayer {
    [[nodiscard]] static auto parse(juce::var const& obj) -> Expected<LottieShapeLayer, String>;

    inline static constexpr auto type = LottieLayerType::shape;

    LottieTransform transform {};
    double inPoint { 0 };
    double outPoint { 0 };
    Vector<LottieShape> shapes {};

    Optional<String> name {};
    Optional<bool> is3D { false };
};

} // namespace mc
