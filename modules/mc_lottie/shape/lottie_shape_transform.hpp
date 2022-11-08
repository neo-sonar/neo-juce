#pragma once

namespace mc {

struct LottieShapeTransform {
    inline static constexpr auto const type   = LottieShapeType::transform;
    inline static constexpr auto const* token = "tr";

    [[nodiscard]] static auto parse(LottieShape group, juce::var const& obj) -> LottieShape;
};

} // namespace mc
