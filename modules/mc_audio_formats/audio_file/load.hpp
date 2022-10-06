#pragma once

namespace mc {

[[nodiscard]] auto loadAudioFile(void const* data, size_t size, juce::AudioFormatManager* formatManager = nullptr)
    -> Optional<BufferWithSampleRate<float>>;

[[nodiscard]] auto loadAudioFile(UniquePtr<juce::InputStream> stream, juce::AudioFormatManager* formatManager = nullptr)
    -> Optional<BufferWithSampleRate<float>>;

} // namespace mc
