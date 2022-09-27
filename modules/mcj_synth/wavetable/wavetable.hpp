#pragma once

namespace mc {

template <typename T>
struct Wavetable {
    using SampleType = T;
    using Ptr        = SharedPtr<Wavetable<T> const>;

    explicit Wavetable(Vector<T> table);
    Wavetable(Vector<T> table, size_t period);

    [[nodiscard]] auto empty() const noexcept -> bool;
    [[nodiscard]] auto size() const noexcept -> size_t;
    [[nodiscard]] auto period() const noexcept -> size_t;

    [[nodiscard]] operator Span<T const>() const noexcept; // NOLINT(hicpp-explicit-conversions)

private:
    Vector<T> _data;
    size_t _period;
};

template <typename T>
[[nodiscard]] auto makeSineWavetable(size_t size) -> typename Wavetable<T>::Ptr;

template <typename T>
[[nodiscard]] auto loadWavetable(UniquePtr<juce::InputStream> stream) -> typename Wavetable<T>::Ptr;

} // namespace mc

#include "wavetable.cpp" // NOLINT(bugprone-suspicious-include)
