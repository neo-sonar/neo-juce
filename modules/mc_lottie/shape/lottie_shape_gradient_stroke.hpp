#pragma once

namespace mc {

struct LottieShapeGradientStroke {
    inline static constexpr auto const type   = LottieShapeType::gradientStroke;
    inline static constexpr auto const* token = "gs";

    [[nodiscard]] static auto parse(LottieShape group, juce::var const& obj) -> LottieShape;
};

} // namespace mc
