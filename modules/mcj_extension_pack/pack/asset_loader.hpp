// SPDX-License-Identifier: BSL-1.0
#pragma once

namespace mc {
struct AssetLoader {
    Vector<juce::File> paths;
    std::function<Vector<juce::File>(juce::File const&)> searcher;
    std::function<Vector<Byte>(Span<Byte const>)> transformer;
};

[[nodiscard]] auto validate(AssetLoader const& loader) -> juce::Result;

} // namespace mc