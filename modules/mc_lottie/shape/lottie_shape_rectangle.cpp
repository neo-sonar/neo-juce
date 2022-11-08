namespace mc {

auto LottieShapeRectangle::parse(LottieShape& group, juce::var const& obj) -> LottieShape
{
    auto rectangle      = LottieShapeRectangle {};
    rectangle.position  = parseLottieVec2(obj["p"]["k"]);
    rectangle.size      = parseLottieVec2(obj["s"]["k"]);
    rectangle.roundness = parseDouble(obj["r"]["k"]);
    group.registry.emplace<LottieShapeRectangle>(group.id, rectangle);
    return group;
}

} // namespace mc
