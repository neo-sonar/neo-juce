namespace mc {
auto LottieLayerNull::parse(entt::registry& reg, juce::var const& obj) -> LottieLayer
{
    checkLayerType(obj, LottieLayerType::null);
    auto layer = LottieLayer { reg, reg.create() };
    parseLottieCommon(reg, layer.id, obj);
    reg.emplace<LottieLayerNull>(layer.id);
    return layer;
}

} // namespace mc
