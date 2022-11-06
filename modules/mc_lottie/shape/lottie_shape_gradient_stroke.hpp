#pragma once

namespace mc {

struct LottieShapeGradientStroke {
    [[nodiscard]] static auto parse(juce::var const& obj) -> LottieShapeGradientStroke;

    inline static constexpr auto const type   = LottieShapeType::gradientStroke;
    inline static constexpr auto const* token = "gs";
};

} // namespace mc
