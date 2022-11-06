namespace mc {

auto loadLottieModel(juce::File const& path) -> Expected<LottieModel, String>
{
    if (not path.existsAsFile()) { return makeUnexpected<String>("invalid path"); }

    auto root = juce::JSON::parse(path);
    return parseLottieModel(root);
}

[[nodiscard]] auto parseLottieModel(juce::var const& root) -> Expected<LottieModel, String>
{
    auto model = LottieModel {};

    if (auto const& name = root["nm"]; not name.isUndefined()) { model.name = name.toString().toStdString(); }
    if (auto const& ver = root["v"]; not ver.isUndefined()) { model.version = ver.toString().toStdString(); }
    if (auto const& ip = root["ip"]; not ip.isUndefined()) { model.ip = static_cast<int>(ip); }
    if (auto const& op = root["op"]; not op.isUndefined()) { model.op = static_cast<int>(op); }
    if (auto const& w = root["w"]; not w.isUndefined()) { model.width = static_cast<int>(w); }
    if (auto const& h = root["h"]; not h.isUndefined()) { model.height = static_cast<int>(h); }
    if (auto const& ddd = root["ddd"]; not ddd.isUndefined()) { model.ddd = static_cast<int>(ddd); }

    auto const* layers = root["layers"].getArray();
    if (layers == nullptr) { return makeUnexpected<String>("no layers defined in model"); }

    for (auto const& layerRoot : *layers) {
        auto layer = parseLottieLayer(layerRoot);
        if (not layer.has_value()) { return makeUnexpected<String>("no layers defined in model"); }
        model.layers.push_back(*layer);
    }

    return model;
}

[[nodiscard]] auto parseLottieLayer(juce::var const& obj) -> Expected<LottieLayer, String>
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

[[nodiscard]] auto parseLottieNullLayer(juce::var const& /*obj*/) -> Expected<LottieNullLayer, String>
{
    return LottieNullLayer {};
}

[[nodiscard]] auto parseLottieShapeLayer(juce::var const& obj) -> Expected<LottieShapeLayer, String>
{
    auto layer = LottieShapeLayer {};
    if (auto const& ip = obj["ip"]; not ip.isUndefined()) { layer.ip = static_cast<int>(ip); }
    if (auto const& op = obj["op"]; not op.isUndefined()) { layer.op = static_cast<int>(op); }
    return layer;
}

} // namespace mc
