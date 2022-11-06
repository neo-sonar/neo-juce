
namespace mc {

auto parseLottieLayer(juce::var const& obj) -> Expected<LottieLayer, String>
{
    auto const& ty = obj["ty"];
    if (ty.isUndefined()) { return makeUnexpected<String>("no layer type"); }

    switch (static_cast<LottieLayerType>(static_cast<int>(ty))) {
    case LottieLayerType::null: return parseLottieNullLayer(obj);
    case LottieLayerType::shape: return parseLottieShapeLayer(obj);
    default: break;
    }

    return makeUnexpected<String>("unhandled layer type");
}

auto name(LottieLayer const& layer) -> Optional<String>
{
    return std::visit([](auto const& l) { return l.name; }, layer);
}

auto inPoint(LottieLayer const& layer) -> double
{
    return std::visit([](auto const& l) { return l.inPoint; }, layer);
}

auto outPoint(LottieLayer const& layer) -> double
{
    return std::visit([](auto const& l) { return l.outPoint; }, layer);
}

} // namespace mc
