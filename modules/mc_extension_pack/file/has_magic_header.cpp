// SPDX-License-Identifier: BSL-1.0

namespace mc {

auto hasMagicHeader(juce::File const& file, std::span<char const> header) -> bool
{
    if (not file.existsAsFile()) { return false; }
    auto const in = file.createInputStream();
    if (in == nullptr) { return false; }
    return hasMagicHeader(*in, header);
}

auto hasMagicHeader(juce::InputStream& in, std::span<char const> header) -> bool
{
    auto heapBuffer  = std::vector<char> {};
    auto stackBuffer = std::array<char, 256> {};
    auto buffer      = std::span<char> { stackBuffer };

    if (buffer.size() < header.size()) {
        heapBuffer.resize(header.size());
        buffer = heapBuffer;
    }

    auto const sz = static_cast<int>(header.size());
    if (in.read(data(buffer), sz) != sz) { return false; }
    auto const content = std::span<char const> { buffer }.first(header.size());
    return hasMagicHeader(content, header);
}

auto hasMagicHeader(std::span<char const> content, std::span<char const> header) -> bool
{
    if (content.size() < header.size()) { return false; }
    return std::equal(header.begin(), header.end(), content.begin());
}

} // namespace mc
