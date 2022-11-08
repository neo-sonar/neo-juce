#pragma once

namespace mc {
struct LottieShapeFill {
    inline static constexpr auto const type   = LottieShapeType::fill;
    inline static constexpr auto const* token = "fl";

    [[nodiscard]] static auto parse(LottieShape& group, juce::var const& obj) -> LottieShape;
};

} // namespace mc
