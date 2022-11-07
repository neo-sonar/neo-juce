namespace mc {

auto makeLottieShapeType(juce::var const& obj) -> LottieShapeType
{
    auto const type = toString(obj["ty"]);
    if (type == LottieShapeRectangle2::token) { return LottieShapeType::rectangle; }
    if (type == LottieShapeEllipse2::token) { return LottieShapeType::ellipse; }
    if (type == LottieShapeFill2::token) { return LottieShapeType::fill; }
    if (type == LottieShapeGradientStroke2::token) { return LottieShapeType::gradientFill; }
    if (type == LottieShapeGradientFill2::token) { return LottieShapeType::gradientStroke; }
    if (type == LottieShapeGroup2::token) { return LottieShapeType::group; }
    if (type == LottieShapePath2::token) { return LottieShapeType::path; }
    if (type == LottieShapeTransform2::token) { return LottieShapeType::transform; }
    if (type == LottieShapeTrim2::token) { return LottieShapeType::trim; }
    raisef<RuntimeError>("unimplemented shape: {}", type);
}

auto LottieShape2::name() const -> String
{
    return tryGetComponent<LottieName>(registry, id).value_or(LottieName {}).name;
}

auto LottieShape2::type() const -> LottieShapeType
{
    return getComponent<LottieShapeType>("LottieShapeType", registry, id);
}

} // namespace mc
