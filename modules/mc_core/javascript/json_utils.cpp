
namespace mc
{
auto JSONUtils::loadFromURL(juce::URL const& url) -> juce::var
{
    auto response = url.createInputStream(false);
    jassert(response != nullptr);
    return juce::JSON::parse(*response);
}
}  // namespace mc