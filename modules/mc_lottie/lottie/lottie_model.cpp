namespace mc {

[[nodiscard]] static auto parseBool(juce::var const& obj) -> bool { return static_cast<bool>(obj); }
[[nodiscard]] static auto parseDouble(juce::var const& obj) -> double { return static_cast<double>(obj); }
[[nodiscard]] static auto parseString(juce::var const& obj) -> String { return obj.toString().toStdString(); }

[[nodiscard]] static auto parseBool(juce::var const& obj, char const* token) -> bool
{
    if (auto const& val = obj[token]; not val.isUndefined()) { return parseBool(val); }
    throw RuntimeError { "invalid type" };
}

[[nodiscard]] static auto parseDouble(juce::var const& obj, char const* token) -> double
{
    if (auto const& val = obj[token]; not val.isUndefined()) { return parseDouble(val); }
    throw RuntimeError { "invalid type" };
}

[[nodiscard]] static auto parseString(juce::var const& obj, char const* token) -> String
{
    if (auto const& val = obj[token]; not val.isUndefined()) { return parseString(val); }
    throw RuntimeError { "invalid type" };
}

[[nodiscard]] static auto parseOptionalBool(juce::var const& obj, char const* token) -> Optional<bool>
{
    if (auto const& val = obj[token]; not val.isUndefined()) { return parseBool(val); }
    return {};
}

[[nodiscard]] static auto parseOptionalDouble(juce::var const& obj, char const* token) -> Optional<double>
{
    if (auto const& val = obj[token]; not val.isUndefined()) { return parseDouble(val); }
    return {};
}

[[nodiscard]] static auto parseOptionalString(juce::var const& obj, char const* token) -> Optional<String>
{
    if (auto const& val = obj[token]; not val.isUndefined()) { return parseString(val); }
    return {};
}

[[nodiscard]] static auto parseLottieTopLevel(juce::var const& obj) -> Expected<LottieModel, String>
{
    auto model      = LottieModel {};
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

template <typename T>
static auto parseLottieLayerCommon(juce::var const& obj, T& layer)
{
    layer.inPoint  = parseDouble(obj, "ip");
    layer.outPoint = parseDouble(obj, "op");
    layer.name     = parseOptionalString(obj, "nm");
    layer.is3D     = parseOptionalBool(obj, "ddd").value_or(false);
}

auto loadLottieModel(juce::File const& path) -> Expected<LottieModel, String>
{
    if (not path.existsAsFile()) { return makeUnexpected<String>("invalid path"); }

    auto root = juce::JSON::parse(path);
    return parseLottieModel(root);
}

auto parseLottieModel(juce::var const& root) -> Expected<LottieModel, String>
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

auto parseLottieNullLayer(juce::var const& obj) -> Expected<LottieNullLayer, String>
{
    auto layer = LottieNullLayer {};
    parseLottieLayerCommon(obj, layer);
    return layer;
}

auto parseLottieShapeLayer(juce::var const& obj) -> Expected<LottieShapeLayer, String>
{
    auto layer = LottieShapeLayer {};
    parseLottieLayerCommon(obj, layer);
    return layer;
}

} // namespace mc
