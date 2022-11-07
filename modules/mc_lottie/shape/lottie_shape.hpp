#pragma once

namespace mc {


struct LottieShape {
    [[nodiscard]] static auto parse(entt::registry& reg, juce::var const& obj) -> LottieShape;

    [[nodiscard]] auto name() const -> String;
    [[nodiscard]] auto type() const -> LottieShapeType;

    entt::registry& registry;
    entt::entity id;
};

struct LottieShapeRectangle {
    inline static constexpr auto const type   = LottieShapeType::rectangle;
    inline static constexpr auto const* token = "rc";

    [[nodiscard]] static auto parse(LottieShape& group, juce::var const& obj) -> LottieShape;

    LottieVec2 position {};
    LottieVec2 size {};
    double roundness {};
};

struct LottieShapeEllipse {
    inline static constexpr auto const type   = LottieShapeType::ellipse;
    inline static constexpr auto const* token = "el";

    [[nodiscard]] static auto parse(LottieShape& group, juce::var const& obj) -> LottieShape;

    LottieVec2 position;
    LottieVec2 size;
};

struct LottieShapeFill {
    inline static constexpr auto const type   = LottieShapeType::fill;
    inline static constexpr auto const* token = "fl";

    [[nodiscard]] static auto parse(LottieShape& group, juce::var const& obj) -> LottieShape;
};

struct LottieShapeGradientFill {
    inline static constexpr auto const type   = LottieShapeType::gradientFill;
    inline static constexpr auto const* token = "gf";

    [[nodiscard]] static auto parse(LottieShape& group, juce::var const& obj) -> LottieShape;
};

struct LottieShapeGradientStroke {
    inline static constexpr auto const type   = LottieShapeType::gradientStroke;
    inline static constexpr auto const* token = "gs";

    [[nodiscard]] static auto parse(LottieShape& group, juce::var const& obj) -> LottieShape;
};

struct LottieShapeGroup {
    inline static constexpr auto const type   = LottieShapeType::group;
    inline static constexpr auto const* token = "gr";

    [[nodiscard]] static auto parse(LottieShape& group, juce::var const& obj) -> LottieShape;

    Vector<LottieShape> shapes;
};

struct LottieShapePath {
    inline static constexpr auto const type   = LottieShapeType::path;
    inline static constexpr auto const* token = "sh";

    [[nodiscard]] static auto parse(LottieShape& group, juce::var const& obj) -> LottieShape;
};

struct LottieShapeTransform {
    inline static constexpr auto const type   = LottieShapeType::transform;
    inline static constexpr auto const* token = "tr";

    [[nodiscard]] static auto parse(LottieShape& group, juce::var const& obj) -> LottieShape;
};

struct LottieShapeTrim {
    inline static constexpr auto const type   = LottieShapeType::trim;
    inline static constexpr auto const* token = "tm";

    [[nodiscard]] static auto parse(LottieShape& group, juce::var const& obj) -> LottieShape;
};

} // namespace mc
