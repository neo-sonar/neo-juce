#pragma once

namespace mc {

struct LottieShapePath {
    inline static constexpr auto const type   = LottieShapeType::path;
    inline static constexpr auto const* token = "sh";

    [[nodiscard]] static auto parse(LottieShape& group, juce::var const& obj) -> LottieShape;
};

} // namespace mc
