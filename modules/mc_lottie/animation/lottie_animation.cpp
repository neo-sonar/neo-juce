namespace mc {

[[nodiscard]] static auto parseLottieTopLevel(juce::var const& obj) -> Expected<LottieAnimation, String>
{
    auto model      = LottieAnimation {};
    model.name      = parseOptionalString(obj, "nm");
    model.version   = parseOptionalString(obj, "v");
    model.inPoint   = parseDouble(obj, "ip");
    model.outPoint  = parseDouble(obj, "op");
    model.width     = parseDouble(obj, "w");
    model.height    = parseDouble(obj, "h");
    model.framerate = parseDouble(obj, "fr");
    model.is3D      = parseOptionalBool(obj, "ddd").value_or(false);
    return model;
}

auto LottieAnimation::load(juce::File const& path) -> Expected<LottieAnimation, String>
{
    if (not path.existsAsFile()) { return makeUnexpected<String>("invalid path"); }

    auto root = juce::JSON::parse(path);
    return LottieAnimation::parse(root);
}

auto LottieAnimation::parse(juce::var const& root) -> Expected<LottieAnimation, String>
{
    auto model = parseLottieTopLevel(root);
    if (not model.has_value()) { return makeUnexpected<String>("failed to parse top-level of model"); }

    auto const* layers = root["layers"].getArray();
    if (layers == nullptr) { return makeUnexpected<String>("no layers defined in model"); }

    for (auto const& layerRoot : *layers) {
        auto layer = parseLottieLayer(layerRoot);
        if (not layer.has_value()) { return makeUnexpected<String>("no layers defined in model"); }
        model->layers.push_back(*layer);
    }

    return *model;
}

} // namespace mc
