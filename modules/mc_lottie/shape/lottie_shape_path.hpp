#pragma once

namespace mc {

struct LottieShapePath {
    [[nodiscard]] static auto parse(juce::var const& obj) -> LottieShapePath;

    inline static constexpr auto const type   = LottieShapeType::path;
    inline static constexpr auto const* token = "sh";
};

} // namespace mc
