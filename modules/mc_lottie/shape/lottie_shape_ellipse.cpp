namespace mc {

auto LottieShapeEllipse::parse(LottieShape& group, juce::var const& obj) -> LottieShape
{
    auto const ellipse = LottieShapeEllipse { parseLottieVec2(obj["p"]["k"]), parseLottieVec2(obj["s"]["k"]) };
    group.registry.emplace<LottieShapeEllipse>(group.id, ellipse);
    return group;
}

} // namespace mc
