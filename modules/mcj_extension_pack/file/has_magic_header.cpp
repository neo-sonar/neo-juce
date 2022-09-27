// SPDX-License-Identifier: BSL-1.0

namespace mc {

auto hasMagicHeader(juce::File const& file, Span<char const> header) -> bool
{
    if (not file.existsAsFile()) { return false; }
    auto const in = file.createInputStream();
    if (in == nullptr) { return false; }
    return hasMagicHeader(*in, header);
}

auto hasMagicHeader(juce::InputStream& in, Span<char const> header) -> bool
{
    auto heapBuffer  = Vector<char> {};
    auto stackBuffer = Array<char, 256> {};
    auto buffer      = Span<char> { stackBuffer };

    if (buffer.size() < header.size()) {
        heapBuffer.resize(header.size());
        buffer = heapBuffer;
    }

    auto const sz = static_cast<int>(header.size());
    if (in.read(data(buffer), sz) != sz) { return false; }
    auto const content = Span<char const> { buffer }.first(header.size());
    return hasMagicHeader(content, header);
}

auto hasMagicHeader(Span<char const> content, Span<char const> header) -> bool
{
    if (content.size() < header.size()) { return false; }
    return std::equal(header.begin(), header.end(), content.begin());
}

} // namespace mc
