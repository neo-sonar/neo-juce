#pragma once

namespace mc {

struct LottieShapeRectangle {
    [[nodiscard]] static auto parse(juce::var const& obj) -> LottieShapeRectangle;

    inline static constexpr auto const type   = LottieShapeType::rectangle;
    inline static constexpr auto const* token = "rc";

    LottieVec2 position {};
    LottieVec2 size {};
    double roundness {};

    Optional<String> name {};
};

} // namespace mc
