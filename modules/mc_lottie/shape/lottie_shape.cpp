namespace mc {

LottieShape::LottieShape(LottieShapeRectangle rectangle) : _shape { std::move(rectangle) } { }

LottieShape::LottieShape(LottieShapeEllipse ellipse) : _shape { std::move(ellipse) } { }

LottieShape::LottieShape(LottieShapeFill fill) : _shape { std::move(fill) } { }

LottieShape::LottieShape(LottieShapeTransform transform) : _shape { std::move(transform) } { }

LottieShape::LottieShape(LottieShapeGroup group) : _shape { std::move(group) } { }

[[nodiscard]] auto LottieShape::isType(LottieShapeType type) const -> bool
{
    return std::visit([type](auto const& s) { return s.type == type; }, _shape);
}

auto LottieShape::parse(juce::var const& obj) -> LottieShape
{
    auto const type = toString(obj["ty"]);
    if (type == LottieShapeRectangle::token) { return LottieShape { LottieShapeRectangle::parse(obj) }; }
    if (type == LottieShapeEllipse::token) { return LottieShape { LottieShapeEllipse::parse(obj) }; }
    if (type == LottieShapeFill::token) { return LottieShape { LottieShapeFill::parse(obj) }; }
    if (type == LottieShapeGroup::token) { return LottieShape { LottieShapeGroup::parse(obj) }; }
    if (type == LottieShapeTransform::token) { return LottieShape { LottieShapeTransform::parse(obj) }; }
    throw RuntimeError { "Unimplemented shape" };
}
} // namespace mc
