namespace mc
{
auto ImageUtils::loadFromURL(juce::URL const& url) -> juce::Image
{
    auto response = url.createInputStream(false);
    auto block    = juce::MemoryBlock {};
    response->readIntoMemoryBlock(block);
    auto mis = juce::MemoryInputStream(block, false);
    return juce::ImageFileFormat::loadFrom(mis);
}
}  // namespace mc