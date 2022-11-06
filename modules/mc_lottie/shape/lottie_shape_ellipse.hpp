#pragma once

namespace mc {

struct LottieShapeEllipse {
    inline static constexpr auto const* token = "el";

    LottieVec2D position;
    LottieVec2D scale;

    Optional<String> name;
};

inline auto parseLottieShapeEllipse(juce::var const& obj) -> LottieShapeEllipse
{
    auto ellipse     = LottieShapeEllipse {};
    ellipse.name     = parseOptionalString(obj, "nm");
    ellipse.position = parseLottieVec2D(obj["p"]["k"]);
    ellipse.scale    = parseLottieVec2D(obj["s"]["k"]);
    return ellipse;
}

} // namespace mc
