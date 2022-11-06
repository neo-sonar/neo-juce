namespace mc {

LottieShape::LottieShape(LottieShapeRectangle rectangle) : _shape { std::move(rectangle) } { }

LottieShape::LottieShape(LottieShapeEllipse ellipse) : _shape { std::move(ellipse) } { }

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
    throw RuntimeError { "Unimplemented shape" };
}
} // namespace mc
