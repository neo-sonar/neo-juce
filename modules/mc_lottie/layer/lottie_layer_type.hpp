#pragma once

namespace mc {

enum struct LottieLayerType {
    precomposition   = 0,
    solidColor       = 1,
    image            = 2,
    null             = 3,
    shape            = 4,
    text             = 5,
    audio            = 6,
    videoPlaceholder = 7,
    imageSequence    = 8,
    video            = 9,
    imagePlaceholder = 10,
    guide            = 11,
    adjustment       = 12,
    camera           = 13,
    light            = 14,
    data             = 15,
};

} // namespace mc
