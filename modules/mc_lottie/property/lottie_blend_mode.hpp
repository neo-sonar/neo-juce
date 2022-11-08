#pragma once

namespace mc {

enum struct LottieBlendMode {
    normal     = 0,
    multiply   = 1,
    screen     = 2,
    overlay    = 3,
    darken     = 4,
    lighten    = 5,
    colorDodge = 6,
    colorBurn  = 7,
    hardLight  = 8,
    softLight  = 9,
    difference = 10,
    exclusion  = 11,
    hue        = 12,
    saturation = 13,
    color      = 14,
    luminosity = 15,
    add        = 16,
    hardMix    = 17,
};

} // namespace mc
