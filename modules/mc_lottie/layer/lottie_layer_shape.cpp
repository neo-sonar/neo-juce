#pragma once

namespace mc {

auto LottieShapeLayer::parse(juce::var const& obj) -> Expected<LottieShapeLayer, String>
{
    auto layer = LottieShapeLayer {};
    parseLottieLayerCommon(obj, layer);

    auto transform = parseLottieTransform(obj["ks"]);
    if (not transform.has_value()) { return makeUnexpected("missing transform"); }
    layer.transform = *transform;

    auto const* shapesArray = obj["shapes"].getArray();
    if (shapesArray == nullptr) { throw InvalidArgument { "no shapes in layer" }; }

    layer.shapes.reserve(static_cast<size_t>(shapesArray->size()));
    for (auto const& shapeObj : *shapesArray) { layer.shapes.push_back(LottieShape::parse(shapeObj)); }

    return layer;
}

} // namespace mc
