#pragma once

namespace mc {

struct LottieShape {

    explicit LottieShape(LottieShapeRectangle rectangle);
    explicit LottieShape(LottieShapeEllipse ellipse);
    explicit LottieShape(LottieShapeFill fill);
    explicit LottieShape(LottieShapeTransform transform);
    explicit LottieShape(LottieShapeGradientFill gradient);
    explicit LottieShape(LottieShapeGradientStroke gradient);
    explicit LottieShape(LottieShapeGroup group);
    explicit LottieShape(LottieShapeTrim trim);
    explicit LottieShape(LottieShapePath path);

    [[nodiscard]] auto isType(LottieShapeType type) const -> bool;

    template <typename ShapeType>
    [[nodiscard]] auto get() const -> ShapeType const*;

    [[nodiscard]] static auto parse(juce::var const& obj) -> LottieShape;

private:
    using Shape = std::variant<    //
        LottieShapeRectangle,      //
        LottieShapeEllipse,        //
        LottieShapeFill,           //
        LottieShapeGradientFill,   //
        LottieShapeGradientStroke, //
        LottieShapeTrim,           //
        LottieShapePath,           //
        LottieShapeTransform,      //
        LottieShapeGroup           //
        >;

    Shape _shape;
};

template <typename ShapeType>
auto LottieShape::get() const -> ShapeType const*
{
    return std::get_if<ShapeType>(&_shape);
}

struct LottieShape2 {
    [[nodiscard]] static auto parse(entt::registry& reg, juce::var const& obj) -> LottieShape2;

    [[nodiscard]] auto name() const -> String;
    [[nodiscard]] auto type() const -> LottieShapeType;

    entt::registry& registry;
    entt::entity id;
};

struct LottieShapeRectangle2 {
    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;

    LottieVec2 position {};
    LottieVec2 size {};
    double roundness {};
};

struct LottieShapeEllipse2 {
    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;

    LottieVec2 position;
    LottieVec2 size;
};

struct LottieShapeFill2 {
    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;
};

struct LottieShapeGradientFill2 {
    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;
};

struct LottieShapeGradientStroke2 {
    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;
};

struct LottieShapeGroup2 {
    inline static constexpr auto const type   = LottieShapeType::group;
    inline static constexpr auto const* token = "gr";

    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;

    Vector<LottieShape2> shapes;
};

struct LottieShapePath2 {
    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;
};

struct LottieShapeTransform2 {
    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;
};

struct LottieShapeTrim2 {
    [[nodiscard]] static auto parse(LottieShape2& group, juce::var const& obj) -> LottieShape2;
};

} // namespace mc
