#ifndef MODERN_CIRCUITS_JUCE_MODULES_AUDIO_BUFFER_POOL_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_AUDIO_BUFFER_POOL_HPP

namespace mc {
class AudioBufferPool {

public:
    /// \brief Construct a AudioBufferPool
    AudioBufferPool() = default;

    /// \brief Destructor
    ~AudioBufferPool() noexcept = default;

    /// \brief Copy constructor is deleted.
    AudioBufferPool(AudioBufferPool const&) = delete;

    /// \brief Copy assignment is deleted.
    auto operator=(AudioBufferPool const&) -> AudioBufferPool& = delete;

    /// \brief Copy constructor is defaulted.
    AudioBufferPool(AudioBufferPool&&) noexcept = default;

    /// \brief Copy assignment is defaulted.
    auto operator=(AudioBufferPool&&) noexcept -> AudioBufferPool& = default;

    /// \brief Allocates the given amount of bytes in the internal storage.
    /// \details This fill free the old storage, so don't use any buffers created
    /// by this instance before the call to reserveBytes.
    /// \param numBytes The number of bytes to allocate.
    auto reserveBytes(std::size_t numBytes) -> void
    {
        capacity_ = numBytes;
        size_     = 0;
        memory_   = std::make_unique<std::uint8_t[]>(numBytes);
    }

    /// \brief Returns the number of used bytes.
    MC_NODISCARD auto sizeInBytes() const noexcept -> std::size_t { return size_; }

    /// \brief Returns the capacity in bytes.
    MC_NODISCARD auto capacityInBytes() const noexcept -> std::size_t { return capacity_; }

    /// \brief Returns an AudioBuffer with the given size.
    /// \param numChannels The number of channels for the newly created AudioBuffer.
    /// \param numSamples The number of samples for the newly created AudioBuffer.
    template <typename FloatType>
    MC_NODISCARD auto makeBuffer(int numChannels, int numSamples) -> std::pair<juce::AudioBuffer<FloatType>, bool>
    {
        static_assert(std::is_same<FloatType, float>::value || std::is_same<FloatType, double>::value, "");

        if (size_ + (sizeof(FloatType) * numChannels * numSamples) < capacity_) {
            auto* data = reinterpret_cast<FloatType*>(&memory_[size_]);
            size_ += sizeof(FloatType) * numChannels * numSamples;
            return std::make_pair(juce::AudioBuffer<FloatType> { &data, numChannels, numSamples }, true);
        }

        return std::make_pair(juce::AudioBuffer<FloatType> {}, false);
    }

private:
    std::unique_ptr<std::uint8_t[]> memory_ {};
    std::size_t capacity_ { 0 };
    std::size_t size_ { 0 };
};
} // namespace mc
#endif // MODERN_CIRCUITS_JUCE_MODULES_AUDIO_BUFFER_POOL_HPP
