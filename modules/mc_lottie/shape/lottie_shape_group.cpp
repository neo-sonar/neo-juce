#pragma once

namespace mc {

auto LottieShapeGroup::parse(juce::var const& obj) -> LottieShapeGroup
{
    if (toString(obj["ty"]) != LottieShapeGroup::token) { throw InvalidArgument { "wrong ty for group shape" }; }
    auto group = LottieShapeGroup {};
    group.name = parseOptionalString(obj, "nm");

    auto const* shapesArray = obj["it"].getArray();
    if (shapesArray == nullptr) { throw InvalidArgument { "no shapes in group" }; }

    group.shapes.reserve(static_cast<size_t>(shapesArray->size()));
    for (auto const shapeObj : *shapesArray) {
        auto shape = makeUnique<LottieShape>(LottieShape::parse(shapeObj));
        group.shapes.push_back(std::move(shape));
    }

    return group;
};

} // namespace mc
