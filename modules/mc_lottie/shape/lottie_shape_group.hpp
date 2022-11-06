#pragma once

namespace mc {

struct LottieShapeGroup {
    inline static constexpr auto const* token = "gr";
    Vector<SharedPtr<LottieShape const>> shapes;
};

} // namespace mc
