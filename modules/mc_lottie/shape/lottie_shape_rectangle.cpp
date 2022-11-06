namespace mc {

auto parseLottieShapeRectangle(juce::var const& obj) -> LottieShapeRectangle
{
    auto rectangle      = LottieShapeRectangle {};
    rectangle.name      = parseOptionalString(obj, "nm");
    rectangle.position  = parseLottieVec2(obj["p"]["k"]);
    rectangle.size      = parseLottieVec2(obj["s"]["k"]);
    rectangle.roundness = parseDouble(obj["r"]["k"]);
    return rectangle;
}

} // namespace mc
