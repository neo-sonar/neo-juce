#pragma once

namespace mc {

struct LottieShapeEllipse {
    inline static constexpr auto const* token = "el";

    LottieVec2 position;
    LottieVec2 size;

    Optional<String> name;
};

[[nodiscard]] auto parseLottieShapeEllipse(juce::var const& obj) -> LottieShapeEllipse;

} // namespace mc
