// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace mc {
auto makeFile(juce::StringRef relativeOrAbsolutePath) -> juce::File
{
    if (juce::File::isAbsolutePath(relativeOrAbsolutePath)) { return juce::File { relativeOrAbsolutePath }; }
    return juce::File::getCurrentWorkingDirectory().getChildFile(relativeOrAbsolutePath);
}

auto makeTemporaryDirectory(juce::StringRef name) -> juce::File
{
    auto const tmpDir = juce::File::getSpecialLocation(juce::File::tempDirectory);
    auto const dir    = tmpDir.getChildFile(name);
    dir.deleteRecursively();
    dir.createDirectory();
    return dir;
}

auto makeChildDirectory(juce::File const& parent, juce::StringRef name) -> juce::File
{
    auto child = parent.getChildFile(name);
    child.createDirectory();
    return child;
}

auto copyFile(juce::File const& src, juce::File const& dest) -> juce::Result
{
    if (not src.copyFileTo(dest)) { return fail("failed to copy file from {} to {}", src, dest); }
    return juce::Result::ok();
}

} // namespace mc

auto juce::VariantConverter<juce::File>::fromVar(juce::var const& v) -> juce::File
{
    return juce::File { v.toString() };
}
auto juce::VariantConverter<juce::File>::toVar(juce::File const& file) -> juce::var { return file.getFullPathName(); }
