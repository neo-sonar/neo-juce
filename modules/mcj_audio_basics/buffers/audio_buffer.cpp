// SPDX-License-Identifier: BSL-1.0

namespace mc {

template <typename T>
auto toVector(juce::AudioBuffer<T> const& buffer) -> Vector<T>
{
    jassert(buffer.getNumChannels() == 1);

    auto vector      = Vector<T>(static_cast<size_t>(buffer.getNumSamples()));
    auto const first = buffer.getReadPointer(0);
    auto const last  = first + buffer.getNumSamples();
    std::copy(first, last, begin(vector));
    return vector;
}

template <typename T>
auto channel(juce::AudioBuffer<T>& buffer, size_t index) -> Span<T>
{
    return { buffer.getWritePointer(static_cast<int>(index)), static_cast<size_t>(buffer.getNumSamples()) };
}

template <typename T>
auto channel(juce::AudioBuffer<T> const& buffer, size_t index) -> Span<T const>
{
    return { buffer.getReadPointer(static_cast<int>(index)), static_cast<size_t>(buffer.getNumSamples()) };
}

} // namespace mc
