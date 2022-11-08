namespace mc {

auto LottieShapeGradientFill::parse(LottieShape group, juce::var const& /*obj*/) -> LottieShape
{
    group.registry.emplace<LottieShapeGradientFill>(group.id);
    return group;
}

} // namespace mc
