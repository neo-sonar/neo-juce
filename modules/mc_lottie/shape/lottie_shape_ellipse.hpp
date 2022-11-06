#pragma once

namespace mc {

struct LottieShapeEllipse {
    [[nodiscard]] static auto parse(juce::var const& obj) -> LottieShapeEllipse;

    inline static constexpr auto const type   = LottieShapeType::ellipse;
    inline static constexpr auto const* token = "el";

    LottieVec2 position;
    LottieVec2 size;

    Optional<String> name;
};

} // namespace mc
