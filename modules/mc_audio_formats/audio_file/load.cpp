namespace mc {

auto loadAudioFile(void const* data, size_t size, juce::AudioFormatManager* formatManager)
    -> Optional<BufferWithSampleRate<float>>
{
    return loadAudioFile(makeUnique<juce::MemoryInputStream>(data, size, false), formatManager);
}

auto loadAudioFile(UniquePtr<juce::InputStream> stream, juce::AudioFormatManager* formatManager)
    -> Optional<BufferWithSampleRate<float>>
{
    if (stream == nullptr) { return {}; }

    auto fallbackManager = juce::AudioFormatManager {};
    if (formatManager == nullptr) {
        fallbackManager.registerBasicFormats();
        formatManager = &fallbackManager;
    }

    auto reader = UniquePtr<juce::AudioFormatReader>(formatManager->createReaderFor(std::move(stream)));
    if (reader == nullptr) { return {}; }

    auto buffer = juce::AudioBuffer<float> {
        static_cast<int>(reader->numChannels),
        static_cast<int>(reader->lengthInSamples),
    };

    reader->read(&buffer, 0, static_cast<int>(reader->lengthInSamples), 0, true, true);
    return BufferWithSampleRate<float> { std::move(buffer), reader->sampleRate };
}

} // namespace mc
