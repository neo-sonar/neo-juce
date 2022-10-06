namespace mc {
auto ImageUtils::loadFromURL(juce::URL const& url) -> juce::Image
{
    auto options  = juce::URL::InputStreamOptions { juce::URL::ParameterHandling::inAddress };
    auto response = url.createInputStream(options);
    auto block    = juce::MemoryBlock {};
    response->readIntoMemoryBlock(block);
    juce::MemoryInputStream mis(block, false);
    return juce::ImageFileFormat::loadFrom(mis);
}
} // namespace mc
