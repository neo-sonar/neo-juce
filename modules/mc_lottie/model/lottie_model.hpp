#pragma once

#include <mc_core/mc_core.hpp>

#include <entt/entt.hpp>

namespace mc {

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

[[nodiscard]] inline static auto parseLottieAnimationHeader(entt::registry& reg, juce::var const& obj) -> entt::entity
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

struct LottieModel {
    [[nodiscard]] static auto load(juce::File const& file) -> LottieModel
    {
        auto const obj = juce::JSON::parse(file);

        auto model = LottieModel {};
        model.root = parseLottieAnimationHeader(model.registry, obj);
        return model;
    }

    entt::registry registry;
    entt::entity root;
};

inline static auto name(LottieModel const& model) -> String const&
{
    auto const& reg = model.registry;
    if (not reg.all_of<mc::LottieName>(model.root)) { raise<InvalidArgument>("missing: LottieName"); }
    return reg.get<mc::LottieName>(model.root).name;
}

inline static auto version(LottieModel const& model) -> String const&
{
    auto const& reg = model.registry;
    if (not reg.all_of<mc::LottieVersion>(model.root)) { raise<InvalidArgument>("missing: LottieVersion"); }
    return reg.get<mc::LottieVersion>(model.root).version;
}

inline static auto inPoint(LottieModel const& model) -> double
{
    auto const& reg = model.registry;
    if (not reg.all_of<mc::LottieInOutPoints>(model.root)) { raise<InvalidArgument>("missing: LottieInOutPoints"); }
    return reg.get<mc::LottieInOutPoints>(model.root).in;
}

inline static auto outPoint(LottieModel const& model) -> double
{
    auto const& reg = model.registry;
    if (not reg.all_of<mc::LottieInOutPoints>(model.root)) { raise<InvalidArgument>("missing: LottieInOutPoints"); }
    return reg.get<mc::LottieInOutPoints>(model.root).out;
}

inline static auto width(LottieModel const& model) -> double
{
    auto const& reg = model.registry;
    if (not reg.all_of<mc::LottieSize2D>(model.root)) { raise<InvalidArgument>("missing: LottieSize2D"); }
    return reg.get<mc::LottieSize2D>(model.root).width;
}

inline static auto height(LottieModel const& model) -> double
{
    auto const& reg = model.registry;
    if (not reg.all_of<mc::LottieSize2D>(model.root)) { raise<InvalidArgument>("missing: LottieSize2D"); }
    return reg.get<mc::LottieSize2D>(model.root).height;
}

inline static auto framerate(LottieModel const& model) -> double
{
    auto const& reg = model.registry;
    if (not reg.all_of<mc::LottieFramerate>(model.root)) { raise<InvalidArgument>("missing: LottieFramerate"); }
    return reg.get<mc::LottieFramerate>(model.root).fps;
}

} // namespace mc