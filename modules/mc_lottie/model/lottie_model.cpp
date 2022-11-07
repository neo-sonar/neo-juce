#pragma once

namespace mc {

[[nodiscard]] static auto parseLottieShape(entt::registry& reg, juce::var const& obj) -> LottieShape2
{
    auto shape      = LottieShape2 { reg, reg.create() };
    auto const type = makeLottieShapeType(obj);
    reg.emplace<LottieShapeType>(shape.id, type);

    if (type == LottieShapeType::rectangle) { return shape; }
    if (type == LottieShapeType::ellipse) { return shape; }
    if (type == LottieShapeType::fill) { return shape; }
    if (type == LottieShapeType::gradientFill) { return shape; }
    if (type == LottieShapeType::gradientStroke) { return shape; }
    if (type == LottieShapeType::group) { return shape; }
    if (type == LottieShapeType::path) { return shape; }
    if (type == LottieShapeType::transform) { return shape; }
    if (type == LottieShapeType::trim) { return shape; }

    raisef<RuntimeError>("unimplemented shape: {}", toString(obj["ty"]));
}

[[nodiscard]] static auto parseLottieShapes(entt::registry& reg, juce::var const& obj) -> Vector<LottieShape2>
{
    auto const* shapesArray = obj["shapes"].getArray();
    if (shapesArray == nullptr) { raise<InvalidArgument>("no shapes in layer"); }

    auto shapes = Vector<LottieShape2> {};
    shapes.reserve(static_cast<size_t>(shapesArray->size()));
    for (auto const& shapeObj : *shapesArray) { shapes.push_back(parseLottieShape(reg, shapeObj)); }
    return shapes;
}

static auto checkLayerType(juce::var const& obj, LottieLayerType expected) -> void
{
    auto const& ty = obj["ty"];
    if (ty.isUndefined()) { raise<InvalidArgument>("no layer type"); }

    auto const type = static_cast<LottieLayerType>(static_cast<int>(ty));
    if (type != expected) { raise<InvalidArgument>("no layer type"); }
}

static auto parseLottieLayerCommon(entt::registry& reg, entt::entity entity, juce::var const& obj)
{
    if (auto n = tryParseLottieName(obj); n) { reg.emplace<LottieName>(entity, std::move(*n)); }
    if (auto const p = tryParseLottieInOutPoints(obj); p) { reg.emplace<LottieInOutPoints>(entity, *p); }
    if (auto const t = tryParseLottieTransform(obj); t) { reg.emplace<LottieTransform>(entity, *t); }
}

[[nodiscard]] static auto parseLottieLayerNull(entt::registry& reg, juce::var const& obj) -> LottieLayer
{
    checkLayerType(obj, LottieLayerType::null);
    auto const layer = reg.create();
    parseLottieLayerCommon(reg, layer, obj);
    return { reg, layer };
}

[[nodiscard]] static auto parseLottieLayerShape(entt::registry& reg, juce::var const& obj) -> LottieLayer
{
    checkLayerType(obj, LottieLayerType::shape);
    auto layer = LottieLayer { reg, reg.create() };
    parseLottieLayerCommon(reg, layer.id, obj);
    layer.shapes = parseLottieShapes(reg, obj);
    return layer;
}

[[nodiscard]] static auto parseLottieLayer(entt::registry& reg, juce::var const& obj) -> LottieLayer
{
    auto const& ty = obj["ty"];
    if (ty.isUndefined()) { raise<InvalidArgument>("no layer type"); }

    switch (static_cast<LottieLayerType>(static_cast<int>(ty))) {
    case LottieLayerType::null: return parseLottieLayerNull(reg, obj);
    case LottieLayerType::shape: return parseLottieLayerShape(reg, obj);
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

[[nodiscard]] static auto parseLottieLayers(entt::registry& reg, juce::var const& obj) -> Vector<LottieLayer>
{
    auto const* layersObj = obj["layers"].getArray();
    if (layersObj == nullptr) { raise<InvalidArgument>("no layers defined in model"); }

    auto layers = Vector<LottieLayer> {};
    for (auto const& layerObj : *layersObj) { layers.push_back(parseLottieLayer(reg, layerObj)); }
    return layers;
}

[[nodiscard]] static auto parseLottieHeader(entt::registry& reg, juce::var const& obj) -> entt::entity
{
    auto const root = reg.create();
    reg.emplace<LottieName>(root, parseLottieName(obj));
    reg.emplace<LottieVersion>(root, parseLottieVersion(obj));
    reg.emplace<LottieInOutPoints>(root, parseLottieInOutPoints(obj));
    reg.emplace<LottieSize2D>(root, parseLottieSize2D(obj));
    reg.emplace<LottieFramerate>(root, parseLottieFramerate(obj));
    return root;
}

LottieModel::LottieModel(juce::File const& file)
{
    auto const obj = juce::JSON::parse(file);
    if (obj == juce::var {}) { raisef<InvalidArgument>("failed to parse lottie json: {}", file); }
    _root   = parseLottieHeader(_registry, obj);
    _layers = parseLottieLayers(_registry, obj);
}

auto LottieModel::name() const -> String const&
{
    return getComponent<LottieName>("LottieName", _registry, _root).name;
}

auto LottieModel::version() const -> String const&
{
    return getComponent<LottieVersion>("LottieVersion", _registry, _root).version;
}

auto LottieModel::inPoint() const -> double
{
    return getComponent<LottieInOutPoints>("LottieInOutPoints", _registry, _root).in;
}

auto LottieModel::outPoint() const -> double
{
    return getComponent<LottieInOutPoints>("LottieInOutPoints", _registry, _root).out;
}

auto LottieModel::width() const -> double { return getComponent<LottieSize2D>("LottieSize2D", _registry, _root).width; }

auto LottieModel::height() const -> double
{
    return getComponent<LottieSize2D>("LottieSize2D", _registry, _root).height;
}

auto LottieModel::framerate() const -> double
{
    return getComponent<LottieFramerate>("LottieFramerate", _registry, _root).fps;
}

auto LottieModel::layers() const -> Vector<LottieLayer> const& { return _layers; }

} // namespace mc
