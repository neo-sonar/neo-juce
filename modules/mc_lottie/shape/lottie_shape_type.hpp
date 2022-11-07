#pragma once

namespace mc {

struct LottieShape;

enum struct LottieShapeType {
    rectangle,
    ellipse,
    polyStar,
    path,
    fill,
    stroke,
    gradientFill,
    gradientStroke,
    noStyle,
    group,
    transform,
    repeater,
    trim,
    roundedCorners,
    puckerBloat,
    merge,
    twist,
    offsetPath,
    zigZag,
};

[[nodiscard]] auto makeLottieShapeType(juce::var const& obj) -> LottieShapeType;

} // namespace mc
