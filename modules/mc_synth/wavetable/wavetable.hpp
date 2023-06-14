#pragma once

namespace mc {

template <typename T>
struct Wavetable {
    using SampleType = T;
    using Ptr        = std::shared_ptr<Wavetable<T> const>;

    explicit Wavetable(std::vector<T> table);
    Wavetable(std::vector<T> table, size_t period);

    [[nodiscard]] auto empty() const noexcept -> bool;
    [[nodiscard]] auto size() const noexcept -> size_t;
    [[nodiscard]] auto period() const noexcept -> size_t;

    [[nodiscard]] operator Span<T const>() const noexcept; // NOLINT(hicpp-explicit-conversions)

private:
    std::vector<T> _data;
    size_t _period;
};

/// \relates Wavetable
template <typename T>
[[nodiscard]] auto makeSineWavetable(size_t size) -> typename Wavetable<T>::Ptr;

/// \relates Wavetable
template <typename T>
[[nodiscard]] auto loadWavetable(std::unique_ptr<juce::InputStream> stream) -> typename Wavetable<T>::Ptr;

} // namespace mc

#include "wavetable.cpp" // NOLINT(bugprone-suspicious-include)
