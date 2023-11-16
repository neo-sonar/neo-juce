// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace neo {

/// \brief Utilities for JSON parsing/loading
/// \tags{Core}
struct JSONUtils {
    /// \brief Loads a JSON web-response into a var object.
    [[nodiscard]] static auto loadFromURL(juce::URL const& url) -> juce::var;
};

} // namespace neo
