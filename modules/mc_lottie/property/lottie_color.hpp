#pragma once

namespace mc {
struct LottieColor {
    inline static constexpr auto const* token = "c";

    [[nodiscard]] static auto parse(juce::var const& obj) -> LottieColor;

    double red { 0.0 };
    double green { 0.0 };
    double blue { 0.0 };
    double alpha { 1.0 };
};

inline auto LottieColor::parse(juce::var const& obj) -> LottieColor
{
    auto const* array = obj.getArray();
    if (array == nullptr) { raise<InvalidArgument>("missing array of color values"); }

    if (array->size() == 3) {
        return {
            static_cast<double>((*array)[0]),
            static_cast<double>((*array)[1]),
            static_cast<double>((*array)[2]),
        };
    }

    if (array->size() == 4) {
        return {
            static_cast<double>((*array)[0]),
            static_cast<double>((*array)[1]),
            static_cast<double>((*array)[2]),
            static_cast<double>((*array)[3]),
        };
    }

    raise<InvalidArgument>("wrong size for array of color values. 3 or 4 (rgb & rgba)");
}

} // namespace mc
