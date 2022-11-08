namespace mc {

auto LottieShapeFill::parse(LottieShape group, juce::var const& /*obj*/) -> LottieShape
{
    group.registry.emplace<LottieShapeFill>(group.id);
    return group;
}

} // namespace mc
