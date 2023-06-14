// SPDX-License-Identifier: BSL-1.0

namespace mc {

auto isZipFile(juce::File const& file) -> bool
{
    auto const in = file.createInputStream();
    if (in == nullptr) { return false; }
    auto const actual = std::array<char, 4> { in->readByte(), in->readByte(), in->readByte(), in->readByte() };
    return actual == std::array<char, 4> { 0x50, 0x4b, 0x03, 0x04 };
}

} // namespace mc
