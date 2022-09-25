#pragma once

namespace mc {
struct ImageUtils {
    [[nodiscard]] static auto loadFromURL(juce::URL const& url) -> juce::Image;
};
} // namespace mc
