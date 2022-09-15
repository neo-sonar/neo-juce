#pragma once

namespace mc {

/// \brief Utilities for JSON parsing/loading
/// \tags{Core}
struct JSONUtils {
    /// \brief Loads a JSON web-response into a var object.
    [[nodiscard]] static auto loadFromURL(juce::URL const& url) -> juce::var;
};

} // namespace mc
