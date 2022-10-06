
auto juce::VariantConverter<juce::Image>::fromVar(juce::var const& v) -> juce::Image
{
    auto* mb = v.getBinaryData();
    if (mb == nullptr) { return {}; }
    return juce::ImageFileFormat::loadFrom(mb->getData(), mb->getSize());
}

auto juce::VariantConverter<juce::Image>::toVar(juce::Image const& i) -> juce::var
{
    juce::MemoryBlock mb {};
    juce::MemoryOutputStream os(mb, false);
    if (!JPEGImageFormat().writeImageToStream(i, os)) { return {}; }
    return mb;
}
