// SPDX-License-Identifier: BSL-1.0

namespace mc {
auto JSONUtils::loadFromURL(juce::URL const& url) -> juce::var
{
    auto options  = juce::URL::InputStreamOptions { juce::URL::ParameterHandling::inAddress };
    auto response = url.createInputStream(options);
    jassert(response != nullptr);
    return juce::JSON::parse(*response);
}
} // namespace mc
