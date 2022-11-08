#pragma once

namespace mc {

struct LottieShapeEllipse {
    inline static constexpr auto const type   = LottieShapeType::ellipse;
    inline static constexpr auto const* token = "el";

    [[nodiscard]] static auto parse(LottieShape& group, juce::var const& obj) -> LottieShape;

    LottieVec2 position;
    LottieVec2 size;
};

} // namespace mc
