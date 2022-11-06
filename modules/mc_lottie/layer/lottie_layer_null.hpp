#pragma once

namespace mc {

struct LottieNullLayer {
    inline static constexpr auto type = LottieLayerType::null;

    juce::AffineTransform transform {};
    double inPoint { 0 };
    double outPoint { 0 };

    Optional<String> name {};
    Optional<bool> is3D { false };
};

[[nodiscard]] auto parseLottieNullLayer(juce::var const& layer) -> Expected<LottieNullLayer, String>;

inline auto parseLottieNullLayer(juce::var const& obj) -> Expected<LottieNullLayer, String>
{
    auto layer = LottieNullLayer {};
    parseLottieLayerCommon(obj, layer);
    return layer;
}

} // namespace mc
