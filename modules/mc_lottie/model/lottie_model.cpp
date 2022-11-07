#pragma once

namespace mc {

[[nodiscard]] static auto parseLottieHeader(entt::registry& reg, juce::var const& obj) -> entt::entity
{
    auto const root = reg.create();

    auto const& nane = obj["nm"];
    if (nane.isUndefined()) { raise<InvalidArgument>("missing name (nm)"); }
    reg.emplace<LottieName>(root, nane.toString().toStdString());

    auto const& version = obj["v"];
    if (version.isUndefined()) { raise<InvalidArgument>("missing version (v)"); }
    reg.emplace<LottieVersion>(root, version.toString().toStdString());

    auto const& inPoint  = obj["ip"];
    auto const& outPoint = obj["op"];
    if (inPoint.isUndefined()) { raise<InvalidArgument>("missing in-point (ip)"); }
    if (outPoint.isUndefined()) { raise<InvalidArgument>("missing out-point (op)"); }
    reg.emplace<LottieInOutPoints>(root, static_cast<double>(inPoint), static_cast<double>(outPoint));

    auto const& width  = obj["w"];
    auto const& height = obj["h"];
    if (width.isUndefined()) { raise<InvalidArgument>("missing width (w)"); }
    if (height.isUndefined()) { raise<InvalidArgument>("missing height (h)"); }
    reg.emplace<LottieSize2D>(root, static_cast<double>(width), static_cast<double>(height));

    auto const& fps = obj["fr"];
    if (fps.isUndefined()) { raise<InvalidArgument>("missing fps (fr)"); }
    reg.emplace<LottieFramerate>(root, static_cast<double>(fps));

    return root;
}

LottieModel::LottieModel(juce::File const& file)
{
    auto const obj = juce::JSON::parse(file);
    if (obj == juce::var {}) { raisef<InvalidArgument>("failed to parse lottie json: {}", file); }
    _root = parseLottieHeader(_registry, obj);
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

auto LottieModel::width() const -> double
{
    return getComponent<LottieSize2D>("LottieSize2D", _registry, _root).width;
}

auto LottieModel::height() const -> double
{
    return getComponent<LottieSize2D>("LottieSize2D", _registry, _root).height;
}

auto LottieModel::framerate() const -> double
{
    return getComponent<LottieFramerate>("LottieFramerate", _registry, _root).fps;
}

} // namespace mc
