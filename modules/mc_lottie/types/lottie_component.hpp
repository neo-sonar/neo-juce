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

} // namespace mc
