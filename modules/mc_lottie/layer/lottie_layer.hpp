#pragma once

namespace mc {

using LottieLayer = variant<LottieNullLayer, LottieShapeLayer>;

[[nodiscard]] auto parseLottieLayer(juce::var const& layer) -> Expected<LottieLayer, String>;

inline auto parseLottieLayer(juce::var const& obj) -> Expected<LottieLayer, String>
{
    auto const& ty = obj["ty"];
    if (ty.isUndefined()) { return makeUnexpected<String>("no layer type"); }

    switch (static_cast<LottieLayerType>(static_cast<int>(ty))) {
    case LottieLayerType::null: return parseLottieNullLayer(obj);
    case LottieLayerType::shape: return parseLottieShapeLayer(obj);
    default: break;
    }

    return makeUnexpected<String>("unhandled layer type");
}

} // namespace mc
