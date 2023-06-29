#pragma once

namespace mc {

[[nodiscard]] auto loadAudioFile(void const* data, size_t size, juce::AudioFormatManager* formatManager = nullptr)
    -> std::optional<BufferWithSampleRate<float>>;

[[nodiscard]] auto loadAudioFile(std::unique_ptr<juce::InputStream> stream, juce::AudioFormatManager* formatManager = nullptr)
    -> std::optional<BufferWithSampleRate<float>>;

} // namespace mc
