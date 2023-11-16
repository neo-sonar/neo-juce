#pragma once

namespace neo {
struct ImageUtils {
    [[nodiscard]] static auto loadFromURL(juce::URL const& url) -> juce::Image;
};
} // namespace neo
