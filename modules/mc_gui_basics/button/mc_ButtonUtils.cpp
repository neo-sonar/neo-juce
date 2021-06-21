namespace mc
{

auto ButtonUtils::mapSVG(juce::DrawableButton& button, char const* svgData, size_t svgSize, juce::Colour color) -> void
{
    auto drawable = juce::Drawable::createFromImageData(svgData, svgSize);
    drawable->replaceColour(juce::Colours::white, juce::Colours::transparentWhite);
    drawable->replaceColour(juce::Colours::black, color);
    button.setImages(drawable.get());
}

}  // namespace mc