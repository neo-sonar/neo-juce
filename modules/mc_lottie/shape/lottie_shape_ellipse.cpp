namespace mc {

auto LottieShapeEllipse::parse(juce::var const& obj) -> LottieShapeEllipse
{
    auto ellipse     = LottieShapeEllipse {};
    ellipse.name     = parseOptionalString(obj, "nm");
    ellipse.position = parseLottieVec2(obj["p"]["k"]);
    ellipse.size     = parseLottieVec2(obj["s"]["k"]);
    return ellipse;
}

} // namespace mc
