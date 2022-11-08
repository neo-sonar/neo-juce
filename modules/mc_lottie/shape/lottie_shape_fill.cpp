namespace mc {

auto LottieShapeFill::parse(LottieShape group, juce::var const&) -> LottieShape
{
    group.registry.emplace<LottieShapeFill>(group.id);
    return group;
}

} // namespace mc
