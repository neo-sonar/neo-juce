// SPDX-License-Identifier: BSL-1.0

namespace neo {

auto validate(AssetLoader const& loader) -> juce::Result
{
    if (loader.paths.empty()) { return fail("No search paths given"); }
    if (not loader.searcher) { return fail("No searcher given"); }
    return juce::Result::ok();
}

} // namespace neo
