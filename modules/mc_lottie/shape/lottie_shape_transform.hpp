#pragma once

namespace mc {

struct LottieShapeTransform {
    [[nodiscard]] static auto parse(juce::var const& obj) -> LottieShapeTransform;

    inline static constexpr auto const type   = LottieShapeType::transform;
    inline static constexpr auto const* token = "tr";
};

} // namespace mc
