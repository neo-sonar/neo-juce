#pragma once

namespace mc {

template <typename Type>
struct AtomicWrapper {
    AtomicWrapper() = default;

    template <typename OtherType>
    AtomicWrapper(OtherType const& other); // NOLINT(hicpp-explicit-conversions)

    AtomicWrapper(AtomicWrapper const& other);
    auto operator=(AtomicWrapper const& other) noexcept -> AtomicWrapper&;

    [[nodiscard]] auto operator==(AtomicWrapper const& other) const noexcept -> bool;
    [[nodiscard]] auto operator!=(AtomicWrapper const& other) const noexcept -> bool;

    [[nodiscard]] operator juce::var() const noexcept; // NOLINT(hicpp-explicit-conversions)
    [[nodiscard]] operator Type() const noexcept;      // NOLINT(hicpp-explicit-conversions)

    std::atomic<Type> value { Type() };
};

template <typename Type>
using CachedAtomic = juce::CachedValue<AtomicWrapper<Type>>;

using CachedAtomicFloat = CachedAtomic<float>;
using CachedAtomicInt   = CachedAtomic<int>;
using CachedAtomicBool  = CachedAtomic<bool>;

template <typename Type>
template <typename OtherType>
AtomicWrapper<Type>::AtomicWrapper(OtherType const& other) // NOLINT(hicpp-explicit-conversions)
{
    value.store(static_cast<Type>(other));
}

template <typename Type>
AtomicWrapper<Type>::AtomicWrapper(AtomicWrapper<Type> const& other)
{
    value.store(other.value);
}

template <typename Type>
auto AtomicWrapper<Type>::operator=(AtomicWrapper<Type> const& other) noexcept -> AtomicWrapper<Type>&
{
    value.store(other.value);
    return *this;
}

template <typename Type>
auto AtomicWrapper<Type>::operator==(AtomicWrapper<Type> const& other) const noexcept -> bool
{
    if constexpr (std::floating_point<Type>) {
        return juce::exactlyEqual(value.load(), other.value.load());
    } else {
        return value.load() == other.value.load();
    }
}

template <typename Type>
auto AtomicWrapper<Type>::operator!=(AtomicWrapper<Type> const& other) const noexcept -> bool
{
    return value.load() != other.value.load();
}

template <typename Type>
AtomicWrapper<Type>::operator juce::var() const noexcept // NOLINT(hicpp-explicit-conversions)
{
    return value.load();
}

template <typename Type>
AtomicWrapper<Type>::operator Type() const noexcept // NOLINT(hicpp-explicit-conversions)
{
    return value.load();
}

} // namespace mc
