#pragma once

namespace mc {

struct LottieShapeTrim {
    [[nodiscard]] static auto parse(juce::var const& obj) -> LottieShapeTrim;

    inline static constexpr auto const type   = LottieShapeType::trim;
    inline static constexpr auto const* token = "tm";
};

} // namespace mc
