#pragma once

namespace mc {

auto LottieShapeLayer::parse(juce::var const& obj) -> Expected<LottieShapeLayer, String>
{
    auto layer = LottieShapeLayer {};
    parseLottieLayerCommon(obj, layer);

    auto transform = parseLottieTransform(obj["ks"]);
    if (not transform.has_value()) { return makeUnexpected("missing transform"); }
    layer.transform = *transform;

    return layer;
}

} // namespace mc
