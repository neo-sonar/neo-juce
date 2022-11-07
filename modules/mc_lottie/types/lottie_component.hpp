#pragma once

namespace mc {

template <typename ComponentType>
auto getComponent(StringView comp, entt::registry const& reg, entt::entity entity) -> ComponentType const&
{
    if (not reg.valid(entity)) { raise<RuntimeError>("invalid entity"); }
    if (not reg.all_of<ComponentType>(entity)) { raisef<RuntimeError>("missing component: {}", comp); }
    return reg.get<ComponentType>(entity);
}

struct LottieName {
    String name;
};

struct LottieVersion {
    String version;
};

struct LottieInOutPoints {
    double in;
    double out;
};

struct LottieFramerate {
    double fps;
};

struct LottieSize2D {
    double width;
    double height;
};

[[nodiscard]] inline auto parseLottieSize2D(juce::var const& obj) -> LottieSize2D
{
    auto const& width  = obj["w"];
    auto const& height = obj["h"];
    if (width.isUndefined()) { raise<InvalidArgument>("missing width (w)"); }
    if (height.isUndefined()) { raise<InvalidArgument>("missing height (h)"); }
    return { static_cast<double>(width), static_cast<double>(height) };
}

[[nodiscard]] inline auto parseLottieInOutPoints(juce::var const& obj) -> LottieInOutPoints
{
    auto const& inPoint  = obj["ip"];
    auto const& outPoint = obj["op"];
    if (inPoint.isUndefined()) { raise<InvalidArgument>("missing in-point (ip)"); }
    if (outPoint.isUndefined()) { raise<InvalidArgument>("missing out-point (op)"); }
    return { static_cast<double>(inPoint), static_cast<double>(outPoint) };
}

[[nodiscard]] inline auto tryParseLottieInOutPoints(juce::var const& obj) -> Optional<LottieInOutPoints>
{
    auto const& inPoint  = obj["ip"];
    auto const& outPoint = obj["op"];
    if (inPoint.isUndefined()) { return {}; }
    if (outPoint.isUndefined()) { return {}; }
    return LottieInOutPoints { static_cast<double>(inPoint), static_cast<double>(outPoint) };
}

[[nodiscard]] inline auto parseLottieName(juce::var const& obj) -> LottieName
{
    auto const& name = obj["nm"];
    if (name.isUndefined()) { raise<InvalidArgument>("missing name (nm)"); }
    return { name.toString().toStdString() };
}

[[nodiscard]] inline auto tryParseLottieName(juce::var const& obj) -> Optional<LottieName>
{
    auto const& name = obj["nm"];
    if (name.isUndefined()) { return {}; }
    return LottieName { name.toString().toStdString() };
}

[[nodiscard]] inline auto parseLottieVersion(juce::var const& obj) -> LottieVersion
{
    auto const& version = obj["v"];
    if (version.isUndefined()) { raise<InvalidArgument>("missing version (v)"); }
    return { version.toString().toStdString() };
}

[[nodiscard]] inline auto parseLottieFramerate(juce::var const& obj) -> LottieFramerate
{
    auto const& fps = obj["fr"];
    if (fps.isUndefined()) { raise<InvalidArgument>("missing fps (fr)"); }
    return { static_cast<double>(fps) };
}

} // namespace mc
