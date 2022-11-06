#pragma once

namespace mc {

struct LottieShapeEllipse {
    inline static constexpr auto const* token = "el";

    LottieVec2 position;
    LottieVec2 scale;

    Optional<String> name;
};

inline auto parseLottieShapeEllipse(juce::var const& obj) -> LottieShapeEllipse
{
    auto ellipse     = LottieShapeEllipse {};
    ellipse.name     = parseOptionalString(obj, "nm");
    ellipse.position = parseLottieVec2(obj["p"]["k"]);
    ellipse.scale    = parseLottieVec2(obj["s"]["k"]);
    return ellipse;
}

} // namespace mc
