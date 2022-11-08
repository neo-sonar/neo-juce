namespace mc {

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

auto LottieShape::name() const -> String
{
    return tryGetComponent<LottieName>(registry, id).value_or(LottieName {}).name;
}

auto LottieShape::type() const -> LottieShapeType
{
    return getComponent<LottieShapeType>("LottieShapeType", registry, id);
}

auto LottieShape::parse(entt::registry& reg, juce::var const& obj) -> LottieShape
{
    auto shape      = LottieShape { reg, reg.create() };
    auto const type = makeLottieShapeType(obj);
    reg.emplace<LottieShapeType>(shape.id, type);

    if (auto n = tryParseLottieName(obj); n) { reg.emplace<LottieName>(shape.id, std::move(*n)); }

    if (type == LottieShapeType::rectangle) { return LottieShapeRectangle::parse(shape, obj); }
    if (type == LottieShapeType::ellipse) { return LottieShapeEllipse::parse(shape, obj); }
    if (type == LottieShapeType::fill) { return LottieShapeFill::parse(shape, obj); }
    if (type == LottieShapeType::gradientFill) { return LottieShapeGradientFill::parse(shape, obj); }
    if (type == LottieShapeType::gradientStroke) { return LottieShapeGradientStroke::parse(shape, obj); }
    if (type == LottieShapeType::group) { return LottieShapeGroup::parse(shape, obj); }
    if (type == LottieShapeType::path) { return LottieShapePath::parse(shape, obj); }
    if (type == LottieShapeType::transform) { return LottieShapeTransform::parse(shape, obj); }
    if (type == LottieShapeType::trim) { return LottieShapeTrim::parse(shape, obj); }

    raisef<RuntimeError>("unimplemented shape: {}", toString(obj["ty"]));
}

} // namespace mc
