// SPDX-License-Identifier: BSL-1.0

namespace mc {

FileSearcher::FileSearcher(juce::String filter, bool recursive)
    : _filter { std::move(filter) }, _recursive { recursive }
{
}

auto FileSearcher::operator()(juce::File const& root) -> Vector<juce::File>
{
    auto files   = Vector<juce::File> {};
    auto it      = juce::RangedDirectoryIterator { root, _recursive, _filter };
    auto getFile = [](auto const& e) { return e.getFile(); };
    std::transform(begin(it), end(it), std::back_inserter(files), getFile);
    return files;
}

} // namespace mc
