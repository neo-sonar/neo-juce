#pragma once

namespace mc {

struct LottieShapeGradientFill {
    [[nodiscard]] static auto parse(juce::var const& obj) -> LottieShapeGradientFill;

    inline static constexpr auto const type   = LottieShapeType::gradientFill;
    inline static constexpr auto const* token = "gf";
};

} // namespace mc
