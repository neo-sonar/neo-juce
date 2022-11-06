#pragma once

namespace mc {

struct LottieShapeGroup {
    [[nodiscard]] static auto parse(juce::var const& obj) -> LottieShapeGroup;

    inline static constexpr auto const type   = LottieShapeType::group;
    inline static constexpr auto const* token = "gr";

    Vector<SharedPtr<LottieShape const>> shapes;
    Optional<String> name;
};

} // namespace mc
