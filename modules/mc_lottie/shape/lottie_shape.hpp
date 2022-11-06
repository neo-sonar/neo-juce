#pragma once

namespace mc {

struct LottieShape {

    explicit LottieShape(LottieShapeRectangle rectangle);
    explicit LottieShape(LottieShapeEllipse ellipse);
    explicit LottieShape(LottieShapeGroup group);

    [[nodiscard]] auto isType(LottieShapeType type) const -> bool;

    template <typename ShapeType>
    [[nodiscard]] auto get() const -> ShapeType const*;

    [[nodiscard]] static auto parse(juce::var const& obj) -> LottieShape;

private:
    using Shape = std::variant< //
        LottieShapeRectangle,   //
        LottieShapeEllipse,     //
        LottieShapeGroup        //
        >;

    Shape _shape;
};

template <typename ShapeType>
auto LottieShape::get() const -> ShapeType const*
{
    return std::get_if<ShapeType>(&_shape);
}

} // namespace mc
