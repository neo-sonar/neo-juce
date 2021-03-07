
#ifndef MC_JUCE_BUNDLE_VALUE_TREE_VALUE_WRAPPER_HPP
#define MC_JUCE_BUNDLE_VALUE_TREE_VALUE_WRAPPER_HPP

namespace mc
{

template<typename Type>
struct AtomicWrapper
{
    AtomicWrapper() = default;

    template<typename OtherType>
    AtomicWrapper(OtherType const& other)
    {
        value.store(other);
    }

    AtomicWrapper(const AtomicWrapper& other) { value.store(other.value); }

    AtomicWrapper& operator=(const AtomicWrapper& other) noexcept
    {
        value.store(other.value);
        return *this;
    }

    bool operator==(const AtomicWrapper& other) const noexcept { return value.load() == other.value.load(); }

    bool operator!=(const AtomicWrapper& other) const noexcept { return value.load() != other.value.load(); }

    operator juce::var() const noexcept { return value.load(); }

    operator Type() const noexcept { return value.load(); }

    std::atomic<Type> value {Type()};
};

template<typename Type, typename Constrainer>
struct ConstrainerWrapper
{
    ConstrainerWrapper() = default;

    template<typename OtherType>
    ConstrainerWrapper(const OtherType& other)
    {
        value = Constrainer::constrain(other);
    }

    ConstrainerWrapper(const ConstrainerWrapper& other) { value = other.value; }

    ConstrainerWrapper& operator=(const ConstrainerWrapper& other) noexcept
    {
        value = Constrainer::constrain(other.value);
        return *this;
    }

    bool operator==(const ConstrainerWrapper& other) const noexcept { return value == other.value; }
    bool operator!=(const ConstrainerWrapper& other) const noexcept { return value != other.value; }

    operator juce::var() const noexcept { return Constrainer::constrain(value); }
    operator Type() const noexcept { return Constrainer::constrain(value); }

    Type value = Type();
};

using CachedAtomicFloat = juce::CachedValue<AtomicWrapper<float>>;
using CachedAtomicInt   = juce::CachedValue<AtomicWrapper<int>>;
using CachedAtomicBool  = juce::CachedValue<AtomicWrapper<bool>>;

}  // namespace mc
#endif  // MC_JUCE_BUNDLE_VALUE_TREE_VALUE_WRAPPER_HPP
