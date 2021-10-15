#ifndef MODERN_CIRCUITS_APP_ZENTRALE_IMAGE_UTILS_HPP
#define MODERN_CIRCUITS_APP_ZENTRALE_IMAGE_UTILS_HPP

namespace mc {
struct ImageUtils {
    MC_NODISCARD static auto loadFromURL(juce::URL const& url) -> juce::Image;
};
} // namespace mc

template <>
struct juce::VariantConverter<juce::Image> {
    static auto fromVar(juce::var const& v) -> juce::Image
    {
        auto* mb = v.getBinaryData();
        if (mb == nullptr) { return {}; }
        return juce::ImageFileFormat::loadFrom(mb->getData(), mb->getSize());
    }

    static auto toVar(juce::Image const& i) -> juce::var
    {
        juce::MemoryBlock mb {};
        juce::MemoryOutputStream os(mb, false);
        if (!JPEGImageFormat().writeImageToStream(i, os)) { return {}; }
        return mb;
    }
};

#endif // MODERN_CIRCUITS_APP_ZENTRALE_IMAGE_UTILS_HPP
