namespace mc {

auto LottieShapePath::parse(LottieShape group, juce::var const& /*obj*/) -> LottieShape
{
    group.registry.emplace<LottieShapePath>(group.id);
    return group;
}

} // namespace mc
