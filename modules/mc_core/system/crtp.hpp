#ifndef MODERN_CIRCUITS_JUCE_MODULES_CRTP_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_CRTP_HPP

namespace mc
{
template<typename Type, template<typename> typename CrtpTag>
class CRTP
{
protected:
    [[nodiscard]] constexpr auto underlying() const noexcept -> Type const& { return static_cast<Type const&>(*this); }

    [[nodiscard]] constexpr auto underlying() noexcept -> Type& { return static_cast<Type&>(*this); }
};
}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_CRTP_HPP
