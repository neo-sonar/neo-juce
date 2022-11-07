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

} // namespace mc
