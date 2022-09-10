#pragma once

namespace mc {
struct ImageUtils {
    MC_NODISCARD static auto loadFromURL(juce::URL const& url) -> juce::Image;
};
} // namespace mc
