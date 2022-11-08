namespace mc {

auto LottieShapeGradientStroke::parse(LottieShape& group, juce::var const&) -> LottieShape
{
    group.registry.emplace<LottieShapeGradientStroke>(group.id);
    return group;
}

} // namespace mc
