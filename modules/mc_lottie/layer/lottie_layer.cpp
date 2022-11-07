
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

} // namespace mc
