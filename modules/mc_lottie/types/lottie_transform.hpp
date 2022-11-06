#pragma once

namespace mc {

struct LottieVec2D {
    double x { 0.0 };
    double y { 0.0 };
};

[[nodiscard]] inline auto parseLottieVec2D(juce::var const& obj) -> LottieVec2D
{
    if (obj.isUndefined()) { throw InvalidArgument { "invalid lottie vec2" }; }
    auto vec = LottieVec2D {};
    return vec;
}

struct LottieTransform {
    LottieVec2D anchor { 0.0, 0.0 };
    LottieVec2D position { 0.0, 0.0 };
    LottieVec2D scale { 100.0, 100.0 };
    double rotation { 0.0 };
    double skew { 0.0 };
    double skewAxis { 0.0 };
    double opacity { 100.0 };
};

[[nodiscard]] inline auto parseLottieTransform(juce::var const& obj) -> Expected<LottieTransform, String>
{
    auto transform   = LottieTransform {};
    transform.anchor = parseLottieVec2D(obj["a"]);
    return transform;
}

} // namespace mc
