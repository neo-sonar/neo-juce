#pragma once

namespace mc {

struct LottieTransform {
    LottieVec2 anchor { 0.0, 0.0 };
    LottieVec2 position { 0.0, 0.0 };
    LottieVec2 scale { 100.0, 100.0 };
    double rotation { 0.0 };
    double skew { 0.0 };
    double skewAxis { 0.0 };
    double opacity { 100.0 };
};

[[nodiscard]] inline auto parseLottieTransform(juce::var const& obj) -> Expected<LottieTransform, String>
{
    auto transform     = LottieTransform {};
    transform.anchor   = parseLottieVec2(obj["a"]["k"]);
    transform.position = parseLottieVec2(obj["p"]["k"]);
    transform.scale    = parseLottieVec2(obj["s"]["k"]);
    transform.rotation = parseOptionalDouble(obj["r"], "k").value_or(0.0);
    transform.skew     = parseOptionalDouble(obj["sk"], "k").value_or(0.0);
    transform.skewAxis = parseOptionalDouble(obj["sa"], "k").value_or(0.0);
    transform.opacity  = parseOptionalDouble(obj["o"], "k").value_or(100.0);
    return transform;
}

[[nodiscard]] inline auto tryParseLottieTransform(juce::var const& obj) -> Optional<LottieTransform>
{
    auto const& ks = obj["ks"];
    if (ks.isUndefined()) { return {}; }
    auto const transform = parseLottieTransform(ks);
    if (not transform.has_value()) { return {}; }
    return *transform;
}

} // namespace mc
