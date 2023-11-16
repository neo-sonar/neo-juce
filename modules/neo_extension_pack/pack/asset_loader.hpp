// SPDX-License-Identifier: BSL-1.0
#pragma once

namespace neo {
struct AssetLoader {
    std::vector<juce::File> paths;
    std::function<std::vector<juce::File>(juce::File const&)> searcher;
    std::function<std::vector<std::byte>(std::span<std::byte const>)> transformer;
};

[[nodiscard]] auto validate(AssetLoader const& loader) -> juce::Result;

} // namespace neo
