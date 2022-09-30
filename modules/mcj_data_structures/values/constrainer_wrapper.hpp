#pragma once
namespace mc {

template <typename Type, typename Constrainer>
struct ConstrainerWrapper {
    ConstrainerWrapper() = default;

    template <typename OtherType>
    ConstrainerWrapper(OtherType const& other) // NOLINT(hicpp-explicit-conversions)
        : value(Constrainer::constrain(static_cast<Type>(other)))
    {
    }

    ConstrainerWrapper(ConstrainerWrapper const& other) : value(other.value) { }

    auto operator=(ConstrainerWrapper const& other) noexcept -> ConstrainerWrapper&
    {
        value = Constrainer::constrain(other.value);
        return *this;
    }

    auto operator==(ConstrainerWrapper const& other) const noexcept -> bool { return value == other.value; }
    auto operator!=(ConstrainerWrapper const& other) const noexcept -> bool { return value != other.value; }

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
