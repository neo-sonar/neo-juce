namespace mc {
auto parseLottieShape(juce::var const& obj) -> LottieShape
{
    auto const type = toString(obj["ty"]);
    if (type == LottieShapeRectangle::token) { return parseLottieShapeRectangle(obj); }
    if (type == LottieShapeEllipse::token) { return parseLottieShapeEllipse(obj); }
    throw RuntimeError { "Unimplemented shape" };
}
} // namespace mc
