
namespace mc {

auto parseLottieLayer(juce::var const& obj) -> Expected<LottieLayer, String>
{
    auto const& ty = obj["ty"];
    if (ty.isUndefined()) { return makeUnexpected<String>("no layer type"); }

    switch (static_cast<LottieLayerType>(static_cast<int>(ty))) {
    case LottieLayerType::precomposition: break;
    case LottieLayerType::solidColor: break;
    case LottieLayerType::image: break;
    case LottieLayerType::null: return parseLottieNullLayer(obj);
    case LottieLayerType::shape: return parseLottieShapeLayer(obj);
    case LottieLayerType::text: break;
    case LottieLayerType::audio: break;
    case LottieLayerType::videoPlaceholder: break;
    case LottieLayerType::imageSequence: break;
    case LottieLayerType::video: break;
    case LottieLayerType::imagePlaceholder: break;
    case LottieLayerType::guide: break;
    case LottieLayerType::adjustment: break;
    case LottieLayerType::camera: break;
    case LottieLayerType::light: break;
    case LottieLayerType::data: break;
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

auto transform(LottieLayer const& layer) -> LottieTransform
{
    return std::visit([](auto const& l) { return l.transform; }, layer);
}
} // namespace mc
