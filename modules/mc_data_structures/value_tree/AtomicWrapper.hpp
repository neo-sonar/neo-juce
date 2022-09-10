#pragma once

namespace mc {

template <typename Type>
struct AtomicWrapper {
    AtomicWrapper() = default;

    template <typename OtherType>
    AtomicWrapper(OtherType const& other); // NOLINT(hicpp-explicit-conversions)

    AtomicWrapper(AtomicWrapper const& other);
    auto operator=(AtomicWrapper const& other) noexcept -> AtomicWrapper&;

    MC_NODISCARD auto operator==(AtomicWrapper const& other) const noexcept -> bool;
    MC_NODISCARD auto operator!=(AtomicWrapper const& other) const noexcept -> bool;

    MC_NODISCARD operator juce::var() const noexcept; // NOLINT(hicpp-explicit-conversions)
    MC_NODISCARD operator Type() const noexcept;      // NOLINT(hicpp-explicit-conversions)

    Atomic<Type> value { Type() };
};

using CachedAtomicFloat = juce::CachedValue<AtomicWrapper<float>>;
using CachedAtomicInt   = juce::CachedValue<AtomicWrapper<int>>;
using CachedAtomicBool  = juce::CachedValue<AtomicWrapper<bool>>;

} // namespace mc

namespace mc {
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
    return value.load() == other.value.load();
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
