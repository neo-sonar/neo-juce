namespace mc {

auto LottieShapeTransform::parse(LottieShape& group, juce::var const&) -> LottieShape
{
    group.registry.emplace<LottieShapeTransform>(group.id);
    return group;
}

} // namespace mc
