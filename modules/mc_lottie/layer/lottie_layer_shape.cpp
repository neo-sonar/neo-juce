#pragma once

namespace mc {

[[nodiscard]] static auto parseLottieShapes(entt::registry& reg, juce::var const& obj) -> Vector<LottieShape>
{
    auto const* shapesArray = obj["shapes"].getArray();
    if (shapesArray == nullptr) { raise<InvalidArgument>("no shapes in layer"); }

    auto shapes = Vector<LottieShape> {};
    shapes.reserve(static_cast<size_t>(shapesArray->size()));
    for (auto const& shapeObj : *shapesArray) { shapes.push_back(LottieShape::parse(reg, shapeObj)); }
    return shapes;
}

auto LottieLayerShape::parse(entt::registry& reg, juce::var const& obj) -> LottieLayer
{
    checkLayerType(obj, LottieLayerType::shape);
    auto layer = LottieLayer { reg, reg.create() };
    parseLottieCommon(reg, layer.id, obj);
    reg.emplace<LottieLayerShape>(layer.id, parseLottieShapes(reg, obj));
    return layer;
}

} // namespace mc
