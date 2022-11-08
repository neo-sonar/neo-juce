namespace mc {

auto LottieShapeFill::parse(LottieShape group, juce::var const& obj) -> LottieShape
{
    group.registry.emplace<LottieShapeFill>(group.id, LottieShapeFill {});
    group.registry.emplace<StaticLottieColor>(group.id, StaticLottieColor::parse(obj["c"]));
    return group;
}

} // namespace mc
