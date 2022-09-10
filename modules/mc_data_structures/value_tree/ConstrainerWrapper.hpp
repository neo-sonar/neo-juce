#pragma once
namespace mc {

template <typename Type, typename Constrainer>
struct ConstrainerWrapper {
    ConstrainerWrapper() = default;

    template <typename OtherType>
    ConstrainerWrapper(const OtherType& other) // NOLINT(hicpp-explicit-conversions)
        : value(Constrainer::constrain(static_cast<Type>(other)))
    {
    }

    ConstrainerWrapper(const ConstrainerWrapper& other) : value(other.value) { }

    auto operator=(const ConstrainerWrapper& other) noexcept -> ConstrainerWrapper&
    {
        value = Constrainer::constrain(other.value);
        return *this;
    }

    auto operator==(const ConstrainerWrapper& other) const noexcept -> bool { return value == other.value; }
    auto operator!=(const ConstrainerWrapper& other) const noexcept -> bool { return value != other.value; }

    operator juce::var() const noexcept // NOLINT(hicpp-explicit-conversions)
    {
        return Constrainer::constrain(value);
    }
    operator Type() const noexcept // NOLINT(hicpp-explicit-conversions)
    {
        return Constrainer::constrain(value);
    }

    Type value = Type();
};

} // namespace mc
