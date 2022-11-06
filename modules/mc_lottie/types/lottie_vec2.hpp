#pragma once

namespace mc {

struct LottieVec2 {
    double x { 0.0 };
    double y { 0.0 };
};

[[nodiscard]] inline auto parseLottieVec2(juce::var const& obj) -> LottieVec2
{
    auto const* array = obj.getArray();
    if (array == nullptr || array->size() != 2) { throw InvalidArgument { "invalid lottie vec2" }; }

    auto vec = LottieVec2 {};
    vec.x    = parseDouble((*array)[0]);
    vec.y    = parseDouble((*array)[1]);
    return vec;
}

} // namespace mc
