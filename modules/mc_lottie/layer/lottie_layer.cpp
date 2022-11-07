
namespace mc {

auto LottieShape2::type() const -> LottieShapeType
{
    return getComponent<LottieShapeType>("LottieShapeType", registry, id);
}

auto LottieLayer2::name() const -> String
{
    return tryGetComponent<LottieName>(registry, id).value_or(LottieName {}).name;
}

auto LottieLayer2::inOutPoints() const -> Optional<LottieInOutPoints>
{
    return tryGetComponent<LottieInOutPoints>(registry, id);
}

auto LottieLayer2::transform() const -> Optional<LottieTransform>
{
    return tryGetComponent<LottieTransform>(registry, id);
}

} // namespace mc
