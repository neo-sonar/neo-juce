// SPDX-License-Identifier: BSL-1.0
#pragma once

namespace mc {

template <typename Spec>
struct ExtensionPackBuilder {
    using AssetType               = typename Spec::AssetType;
    static constexpr auto version = Spec::version;
    FlatMap<AssetType, AssetLoader> loaders;
};

template <typename Spec>
[[nodiscard]] auto build(ExtensionPackBuilder<Spec> const& builder) -> juce::Result
{
    if (builder.loaders.empty()) { return fail("No loaders registered"); }
    for (auto const& [type, loader] : builder.loaders) {
        if (auto v = validate(loader); v.failed()) { return v; }
    }
    return juce::Result::ok();
}

} // namespace mc
