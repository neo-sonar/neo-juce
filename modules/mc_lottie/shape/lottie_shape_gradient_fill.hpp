#pragma once

namespace mc {

struct LottieShapeGradientFill {
    inline static constexpr auto const type   = LottieShapeType::gradientFill;
    inline static constexpr auto const* token = "gf";

    [[nodiscard]] static auto parse(LottieShape group, juce::var const& obj) -> LottieShape;
};

} // namespace mc
