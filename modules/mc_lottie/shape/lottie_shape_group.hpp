#pragma once

namespace mc {

struct LottieShapeGroup {
    inline static constexpr auto const type   = LottieShapeType::group;
    inline static constexpr auto const* token = "gr";

    [[nodiscard]] static auto parse(LottieShape group, juce::var const& obj) -> LottieShape;

    Vector<LottieShape> shapes;
};

} // namespace mc
