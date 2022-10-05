// SPDX-License-Identifier: BSL-1.0
#pragma once

namespace mc {
struct FileSearcher {
    explicit FileSearcher(juce::String filter, bool recursive = true);

    [[nodiscard]] auto operator()(juce::File const& root) -> Vector<juce::File>;

private:
    juce::String _filter;
    bool _recursive;
};

} // namespace mc