#pragma once

namespace mc {

struct LottieShapeRectangle {
    inline static constexpr auto const type   = LottieShapeType::rectangle;
    inline static constexpr auto const* token = "rc";

    [[nodiscard]] static auto parse(LottieShape& group, juce::var const& obj) -> LottieShape;

    LottieVec2 position {};
    LottieVec2 size {};
    double roundness {};
};

} // namespace mc
