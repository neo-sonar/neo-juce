#pragma once

namespace mc {

struct LottieNullLayer {
    [[nodiscard]] static auto parse(juce::var const& obj) -> Expected<LottieNullLayer, String>;

    inline static constexpr auto type = LottieLayerType::null;

    LottieTransform transform {};
    double inPoint { 0 };
    double outPoint { 0 };

    Optional<String> name {};
    Optional<bool> is3D { false };
};

inline auto LottieNullLayer::parse(juce::var const& obj) -> Expected<LottieNullLayer, String>
{
    auto layer = LottieNullLayer {};
    parseLottieLayerCommon(obj, layer);
    return layer;
}

} // namespace mc
