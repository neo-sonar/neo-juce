#pragma once

namespace mc {
struct LottieColor {
    inline static constexpr auto const* token = "c";

    [[nodiscard]] static auto parse(juce::var const& obj) -> LottieColor;

    double red { 0.0 };
    double green { 0.0 };
    double blue { 0.0 };
};

inline auto LottieColor::parse(juce::var const& obj) -> LottieColor
{
    auto const* array = obj.getArray();
    if (array == nullptr) { raise<InvalidArgument>("missing array of color values"); }
    if (array->size() != 3) { raise<InvalidArgument>("wrong size for array of color values"); }
    return {
        static_cast<double>((*array)[0]),
        static_cast<double>((*array)[1]),
        static_cast<double>((*array)[2]),
    };
}

} // namespace mc
