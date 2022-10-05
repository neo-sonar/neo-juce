// SPDX-License-Identifier: BSL-1.0

namespace mc {

FileSearcher::FileSearcher(juce::String filter, bool recursive)
    : _filter { std::move(filter) }, _recursive { recursive }
{
}

auto FileSearcher::operator()(juce::File const& root) -> Vector<juce::File>
{
    auto files   = Vector<juce::File> {};
    auto it      = juce::RangedDirectoryIterator { root, true, _filter };
    auto getFile = [](auto const& e) { return e.getFile(); };
    std::transform(begin(it), end(it), std::back_inserter(files), getFile);
    return files;
}

auto relativePathsToFiles(Span<String const> relPaths) -> Vector<juce::File>
{
    auto const cwd = juce::File::getCurrentWorkingDirectory();
    auto toFile    = [&cwd](auto const& path) { return cwd.getChildFile(path); };
    auto files     = Vector<juce::File>(relPaths.size());
    ranges::transform(relPaths, ranges::begin(files), toFile);
    return files;
}
} // namespace mc