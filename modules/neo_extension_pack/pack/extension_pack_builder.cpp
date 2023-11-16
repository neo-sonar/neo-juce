// SPDX-License-Identifier: BSL-1.0

namespace neo {

namespace {

[[nodiscard]] auto validate(FlatMap<std::string, AssetLoader> const& loaders) -> juce::Result
{
    if (loaders.empty()) { return fail("No loaders registered"); }
    for (auto const& [type, loader] : loaders) {
        if (auto v = validate(loader); v.failed()) { return v; }
    }
    return juce::Result::ok();
}

[[nodiscard]] auto loadAssetFilePaths(FlatMap<std::string, AssetLoader> const& loaders)
{
    auto files = FlatMap<std::string, std::vector<juce::File>> {};
    for (auto const& [type, loader] : loaders) {
        files[type] = {};
        for (auto const& path : loader.paths) { files[type] = loader.searcher(path); }
    }
    return files;
}

[[nodiscard]] auto validate(FlatMap<std::string, std::vector<juce::File>> const& fileGroups) -> juce::Result
{
    if (fileGroups.empty()) { return fail("No fileGroups found with searchers"); }
    for (auto const& [type, files] : fileGroups) {
        if (files.empty()) { return fail("No files found for type: {}", type); }
    }
    return juce::Result::ok();
}

[[nodiscard]] auto transformFileContent(juce::File const& srcFile,
    juce::File const& destDir,
    std::function<std::vector<std::byte>(std::span<std::byte const>)> const& transformer) -> juce::Result
{
    auto const destFile = destDir.getChildFile(srcFile.getFileName());
    if (not transformer) { return copyFile(srcFile, destFile); }

    auto const input = loadFileAsBytes(srcFile);
    if (input.empty()) { return fail("failed to load content of file: {}", srcFile); }

    auto const output = transformer(input);
    if (output.empty()) { return fail("failed to transform content of file: {}", srcFile); }

    auto out = destFile.createOutputStream();
    if (out == nullptr) { return fail("failed to write content to file: {}", destFile); }
    if (not out->write(output.data(), output.size())) { return fail("failed to write content to file: {}", destFile); }

    return juce::Result::ok();
}

} // namespace

auto build(ExtensionPackBuilder const& builder) -> juce::Result
{
    if (auto result = validate(builder.loaders); result.failed()) { return result; }

    auto const assetFilesGroups = loadAssetFilePaths(builder.loaders);
    if (auto result = validate(assetFilesGroups); result.failed()) { return result; }

    auto const workDir = makeTemporaryDirectory("builder_tmp");
    if (not workDir.isDirectory()) { return fail("failed to create tmp work dir: {}", workDir); }
    // SCOPE_EXIT { workDir.deleteRecursively(); }; // TODO(reenable)

    for (auto const& [type, group] : assetFilesGroups) {
        auto const& transformer = builder.loaders.at(type).transformer;

        auto const assetDir = makeChildDirectory(workDir, type);
        if (not assetDir.isDirectory()) { return fail("failed to create tmp asset dir: {}", assetDir); }

        for (auto const& asset : group) {
            if (auto result = transformFileContent(asset, assetDir, transformer); result.failed()) { return result; }
        }
    }

    return juce::Result::ok();
}

} // namespace neo
