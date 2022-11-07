namespace mc {

LottieShape::LottieShape(LottieShapeRectangle rectangle) : _shape { std::move(rectangle) } { }

LottieShape::LottieShape(LottieShapeEllipse ellipse) : _shape { std::move(ellipse) } { }

LottieShape::LottieShape(LottieShapeFill fill) : _shape { std::move(fill) } { }

LottieShape::LottieShape(LottieShapeGradientStroke gradient) : _shape { std::move(gradient) } { }

LottieShape::LottieShape(LottieShapeGradientFill gradient) : _shape { std::move(gradient) } { }

LottieShape::LottieShape(LottieShapeTrim trim) : _shape { std::move(trim) } { }

LottieShape::LottieShape(LottieShapePath path) : _shape { std::move(path) } { }

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
    if (type == LottieShapeGradientStroke::token) { return LottieShape { LottieShapeGradientStroke::parse(obj) }; }
    if (type == LottieShapeGradientFill::token) { return LottieShape { LottieShapeGradientFill::parse(obj) }; }
    if (type == LottieShapeGroup::token) { return LottieShape { LottieShapeGroup::parse(obj) }; }
    if (type == LottieShapePath::token) { return LottieShape { LottieShapePath::parse(obj) }; }
    if (type == LottieShapeTransform::token) { return LottieShape { LottieShapeTransform::parse(obj) }; }
    if (type == LottieShapeTrim::token) { return LottieShape { LottieShapeTrim::parse(obj) }; }
    raisef<RuntimeError>("unimplemented shape: {}", type);
}

auto makeLottieShapeType(juce::var const& obj) -> LottieShapeType
{
    auto const type = toString(obj["ty"]);
    if (type == LottieShapeRectangle::token) { return LottieShapeType::rectangle; }
    if (type == LottieShapeEllipse::token) { return LottieShapeType::ellipse; }
    if (type == LottieShapeFill::token) { return LottieShapeType::fill; }
    if (type == LottieShapeGradientStroke::token) { return LottieShapeType::gradientFill; }
    if (type == LottieShapeGradientFill::token) { return LottieShapeType::gradientStroke; }
    if (type == LottieShapeGroup::token) { return LottieShapeType::group; }
    if (type == LottieShapePath::token) { return LottieShapeType::path; }
    if (type == LottieShapeTransform::token) { return LottieShapeType::transform; }
    if (type == LottieShapeTrim::token) { return LottieShapeType::trim; }
    raisef<RuntimeError>("unimplemented shape: {}", type);
}

} // namespace mc
