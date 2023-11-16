// SPDX-License-Identifier: BSL-1.0

namespace neo {

template <typename T>
auto toVector(juce::AudioBuffer<T> const& buffer) -> std::vector<T>
{
    jassert(buffer.getNumChannels() == 1);

    auto vector      = std::vector<T>(static_cast<size_t>(buffer.getNumSamples()));
    auto const first = buffer.getReadPointer(0);
    auto const last  = first + buffer.getNumSamples();
    std::copy(first, last, begin(vector));
    return vector;
}

template <typename T>
auto channel(juce::AudioBuffer<T>& buffer, size_t index) -> std::span<T>
{
    return { buffer.getWritePointer(static_cast<int>(index)), static_cast<size_t>(buffer.getNumSamples()) };
}

template <typename T>
auto channel(juce::AudioBuffer<T> const& buffer, size_t index) -> std::span<T const>
{
    return { buffer.getReadPointer(static_cast<int>(index)), static_cast<size_t>(buffer.getNumSamples()) };
}

} // namespace neo
