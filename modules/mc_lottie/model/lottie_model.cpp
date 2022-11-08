#pragma once

namespace mc {

[[nodiscard]] static auto parseLottieLayers(entt::registry& reg, juce::var const& obj) -> Vector<LottieLayer>
{
    auto const* layersObj = obj["layers"].getArray();
    if (layersObj == nullptr) { raise<InvalidArgument>("no layers defined in model"); }

    auto layers = Vector<LottieLayer> {};
    for (auto const& layerObj : *layersObj) { layers.push_back(LottieLayer::parse(reg, layerObj)); }
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
