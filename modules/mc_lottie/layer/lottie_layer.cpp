
namespace mc {

auto LottieLayer::name() const -> String
{
    return tryGetComponent<LottieName>(registry, id).value_or(LottieName {}).name;
}

auto LottieLayer::inOutPoints() const -> Optional<LottieInOutPoints>
{
    return tryGetComponent<LottieInOutPoints>(registry, id);
}

auto LottieLayer::transform() const -> Optional<LottieTransform>
{
    return tryGetComponent<LottieTransform>(registry, id);
}

auto LottieLayer::parse(entt::registry& reg, juce::var const& obj) -> LottieLayer
{
    auto const& ty = obj["ty"];
    if (ty.isUndefined()) { raise<InvalidArgument>("no layer type"); }

    switch (static_cast<LottieLayerType>(static_cast<int>(ty))) {
    case LottieLayerType::null: return LottieLayerNull::parse(reg, obj);
    case LottieLayerType::shape: return LottieLayerShape::parse(reg, obj);
    case LottieLayerType::precomposition:
    case LottieLayerType::solidColor:
    case LottieLayerType::image:
    case LottieLayerType::text:
    case LottieLayerType::audio:
    case LottieLayerType::videoPlaceholder:
    case LottieLayerType::imageSequence:
    case LottieLayerType::video:
    case LottieLayerType::imagePlaceholder:
    case LottieLayerType::guide:
    case LottieLayerType::adjustment:
    case LottieLayerType::camera:
    case LottieLayerType::light:
    case LottieLayerType::data: break;
    }

    raise<InvalidArgument>("unhandled layer type");
}
} // namespace mc
