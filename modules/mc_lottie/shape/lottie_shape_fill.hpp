#pragma once

namespace mc {

struct LottieShapeFill {
    [[nodiscard]] static auto parse(juce::var const& obj) -> LottieShapeFill;

    inline static constexpr auto const type   = LottieShapeType::fill;
    inline static constexpr auto const* token = "fl";
};

} // namespace mc
