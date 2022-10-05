// SPDX-License-Identifier: BSL-1.0

namespace mc {

static auto validate(FlatMap<String, AssetLoader> const& loaders) -> juce::Result
{
    if (loaders.empty()) { return fail("No loaders registered"); }
    for (auto const& [type, loader] : loaders) {
        if (auto v = validate(loader); v.failed()) { return v; }
    }
    return juce::Result::ok();
}

static auto loadAssetFilePaths(FlatMap<String, AssetLoader> const& loaders)
{
    auto files = FlatMap<String, Vector<juce::File>> {};
    for (auto const& [type, loader] : loaders) {
        files[type] = {};
        for (auto const& path : loader.paths) { files[type] = loader.searcher(path); }
    }
    return files;
}

static auto validate(FlatMap<String, Vector<juce::File>> const& fileGroups) -> juce::Result
{
    if (fileGroups.empty()) { return fail("No fileGroups found with searchers"); }
    for (auto const& [type, files] : fileGroups) {
        if (files.empty()) { return fail("No files found for type: {}", type); }
    }
    return juce::Result::ok();
}

auto build(ExtensionPackBuilder const& builder) -> juce::Result
{
    if (auto result = validate(builder.loaders); result.failed()) { return result; }

    auto const files = loadAssetFilePaths(builder.loaders);
    if (auto result = validate(files); result.failed()) { return result; }

    return juce::Result::ok();
}

} // namespace mc
