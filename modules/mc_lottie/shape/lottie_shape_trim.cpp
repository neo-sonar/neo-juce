namespace mc {

auto LottieShapeTrim::parse(LottieShape group, juce::var const&) -> LottieShape
{
    group.registry.emplace<LottieShapeTrim>(group.id);
    return group;
}

} // namespace mc
