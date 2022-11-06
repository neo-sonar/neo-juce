#pragma once

namespace mc {

struct LottieShapeRectangle {
    inline static constexpr auto const* token = "rc";

    LottieVec2 position {};
    LottieVec2 size {};
    double roundness {};

    Optional<String> name {};
};

[[nodiscard]] auto parseLottieShapeRectangle(juce::var const& obj) -> LottieShapeRectangle;

} // namespace mc
