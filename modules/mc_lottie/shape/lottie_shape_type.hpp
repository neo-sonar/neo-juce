#pragma once

namespace mc {
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

struct LottieShapeRectangle;
struct LottieShapeEllipse;
struct LottieShapePolyStar;
struct LottieShapePath;
struct LottieShapeFill;
struct LottieShapeStroke;
struct LottieShapeGradientFill;
struct LottieShapeGradientStroke;
struct LottieShapeNoStyle;
struct LottieShapeGroup;
struct LottieShapeTransform;
struct LottieShapeRepeater;
struct LottieShapeTrim;
struct LottieShapeRoundedCorners;
struct LottieShapePuckerBloat;
struct LottieShapeMerge;
struct LottieShapeTwist;
struct LottieShapeOffsetPath;
struct LottieShapeZigZag;

using LottieShape = std::variant< //
    LottieShapeRectangle,         //
    LottieShapeEllipse,           //
    LottieShapeGroup              //
    >;

} // namespace mc
