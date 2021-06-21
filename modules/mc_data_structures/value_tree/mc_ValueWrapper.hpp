
#ifndef MC_JUCE_BUNDLE_VALUE_TREE_VALUE_WRAPPER_HPP
#define MC_JUCE_BUNDLE_VALUE_TREE_VALUE_WRAPPER_HPP

namespace mc
{

template<typename Type>
struct AtomicWrapper
{
    AtomicWrapper() = default;

    template<typename OtherType>
    AtomicWrapper(OtherType const& other)  // NOLINT(hicpp-explicit-conversions)
    {
        value.store(static_cast<Type>(other));
    }

    AtomicWrapper(const AtomicWrapper& other) { value.store(other.value); }

    auto operator=(const AtomicWrapper& other) noexcept -> AtomicWrapper&
    {
        value.store(other.value);
        return *this;
    }

    auto operator==(const AtomicWrapper& other) const noexcept -> bool { return value.load() == other.value.load(); }

    auto operator!=(const AtomicWrapper& other) const noexcept -> bool { return value.load() != other.value.load(); }

    operator juce::var() const noexcept  // NOLINT(hicpp-explicit-conversions)
    {
        return value.load();
    }

    operator Type() const noexcept  // NOLINT(hicpp-explicit-conversions)
    {
        return value.load();
    }

    std::atomic<Type> value {Type()};
};

template<typename Type, typename Constrainer>
struct ConstrainerWrapper
{
    ConstrainerWrapper() = default;

    template<typename OtherType>
    ConstrainerWrapper(const OtherType& other)  // NOLINT(hicpp-explicit-conversions)
    {
        value = Constrainer::constrain(static_cast<Type>(other));
    }

    ConstrainerWrapper(const ConstrainerWrapper& other) { value = other.value; }

    auto operator=(const ConstrainerWrapper& other) noexcept -> ConstrainerWrapper&
    {
        value = Constrainer::constrain(other.value);
        return *this;
    }

    auto operator==(const ConstrainerWrapper& other) const noexcept -> bool { return value == other.value; }
    auto operator!=(const ConstrainerWrapper& other) const noexcept -> bool { return value != other.value; }

    operator juce::var() const noexcept  // NOLINT(hicpp-explicit-conversions)
    {
        return Constrainer::constrain(value);
    }
    operator Type() const noexcept  // NOLINT(hicpp-explicit-conversions)
    {
        return Constrainer::constrain(value);
    }

    Type value = Type();
};

using CachedAtomicFloat = juce::CachedValue<AtomicWrapper<float>>;
using CachedAtomicInt   = juce::CachedValue<AtomicWrapper<int>>;
using CachedAtomicBool  = juce::CachedValue<AtomicWrapper<bool>>;

}  // namespace mc
#endif  // MC_JUCE_BUNDLE_VALUE_TREE_VALUE_WRAPPER_HPP
