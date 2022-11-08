#pragma once

namespace mc {

struct LottieShapeTrim {
    inline static constexpr auto const type   = LottieShapeType::trim;
    inline static constexpr auto const* token = "tm";

    [[nodiscard]] static auto parse(LottieShape& group, juce::var const& obj) -> LottieShape;
};

} // namespace mc
