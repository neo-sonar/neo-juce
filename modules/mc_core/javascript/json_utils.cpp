
namespace mc
{
auto JSONUtils::loadFromURL(juce::URL const& url) -> juce::var
{
    auto response = url.createInputStream(false);
    return juce::JSON::parse(*response);
}
}  // namespace mc