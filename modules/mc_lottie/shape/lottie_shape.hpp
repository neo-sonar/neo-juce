#pragma once

namespace mc {


struct LottieShape2 {
    [[nodiscard]] static auto parse(entt::registry& reg, juce::var const& obj) -> LottieShape2;

    [[nodiscard]] auto name() const -> String;
    [[nodiscard]] auto type() const -> LottieShapeType;

    entt::registry& registry;
    entt::entity id;
};

struct LottieShapeRectangle2 {
    inline static constexpr auto const type   = LottieShapeType::rectangle;
    inline static constexpr auto const* token = "rc";

    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;

    LottieVec2 position {};
    LottieVec2 size {};
    double roundness {};
};

struct LottieShapeEllipse2 {
    inline static constexpr auto const type   = LottieShapeType::ellipse;
    inline static constexpr auto const* token = "el";

    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;

    LottieVec2 position;
    LottieVec2 size;
};

struct LottieShapeFill2 {
    inline static constexpr auto const type   = LottieShapeType::fill;
    inline static constexpr auto const* token = "fl";

    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;
};

struct LottieShapeGradientFill2 {
    inline static constexpr auto const type   = LottieShapeType::gradientFill;
    inline static constexpr auto const* token = "gf";

    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;
};

struct LottieShapeGradientStroke2 {
    inline static constexpr auto const type   = LottieShapeType::gradientStroke;
    inline static constexpr auto const* token = "gs";

    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;
};

struct LottieShapeGroup2 {
    inline static constexpr auto const type   = LottieShapeType::group;
    inline static constexpr auto const* token = "gr";

    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;

    Vector<LottieShape2> shapes;
};

struct LottieShapePath2 {
    inline static constexpr auto const type   = LottieShapeType::path;
    inline static constexpr auto const* token = "sh";

    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;
};

struct LottieShapeTransform2 {
    inline static constexpr auto const type   = LottieShapeType::transform;
    inline static constexpr auto const* token = "tr";

    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;
};

struct LottieShapeTrim2 {
    inline static constexpr auto const type   = LottieShapeType::trim;
    inline static constexpr auto const* token = "tm";

    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;
};

} // namespace mc
