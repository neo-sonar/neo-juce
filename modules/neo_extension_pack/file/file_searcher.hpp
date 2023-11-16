// SPDX-License-Identifier: BSL-1.0
#pragma once

namespace neo {
struct FileSearcher {
    explicit FileSearcher(juce::String filter, bool recursive = true);

    [[nodiscard]] auto operator()(juce::File const& root) -> std::vector<juce::File>;

private:
    juce::String _filter;
    bool _recursive;
};

} // namespace neo
