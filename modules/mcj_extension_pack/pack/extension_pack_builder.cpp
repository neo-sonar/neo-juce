// SPDX-License-Identifier: BSL-1.0

namespace mc {

auto build(ExtensionPackBuilder const& builder) -> juce::Result
{
    if (builder.loaders.empty()) { return fail("No loaders registered"); }
    for (auto const& [type, loader] : builder.loaders) {
        if (auto v = validate(loader); v.failed()) { return v; }
    }
    return juce::Result::ok();
}

} // namespace mc
