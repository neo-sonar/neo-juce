// SPDX-License-Identifier: BSL-1.0
#pragma once

namespace mc {
struct AssetLoader {
    std::vector<juce::File> paths;
    std::function<std::vector<juce::File>(juce::File const&)> searcher;
    std::function<std::vector<Byte>(Span<Byte const>)> transformer;
};

[[nodiscard]] auto validate(AssetLoader const& loader) -> juce::Result;

} // namespace mc
