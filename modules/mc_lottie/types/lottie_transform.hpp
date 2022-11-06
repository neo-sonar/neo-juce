#pragma once

namespace mc {

struct LottieVec2D {
    double x { 0.0 };
    double y { 0.0 };
};

[[nodiscard]] inline auto parseLottieVec2D(juce::var const& obj) -> LottieVec2D
{
    auto const* array = obj.getArray();
    if (array == nullptr || array->size() != 2) { throw InvalidArgument { "invalid lottie vec2" }; }

    auto vec = LottieVec2D {};
    vec.x    = parseDouble((*array)[0]);
    vec.y    = parseDouble((*array)[1]);
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
    auto transform     = LottieTransform {};
    transform.anchor   = parseLottieVec2D(obj["a"]["k"]);
    transform.position = parseLottieVec2D(obj["p"]["k"]);
    transform.scale    = parseLottieVec2D(obj["s"]["k"]);
    transform.rotation = parseOptionalDouble(obj["r"], "k").value_or(0.0);
    transform.skew     = parseOptionalDouble(obj["sk"], "k").value_or(0.0);
    transform.skewAxis = parseOptionalDouble(obj["sa"], "k").value_or(0.0);
    transform.opacity  = parseOptionalDouble(obj["o"], "k").value_or(100.0);
    return transform;
}

} // namespace mc
