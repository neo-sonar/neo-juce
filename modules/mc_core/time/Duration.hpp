#pragma once

namespace mc {

namespace detail {
template <typename T, bool isFloatingPoint = std::is_floating_point<T>::value>
struct DurationFromVarImpl {
    auto operator()(juce::var const& v) -> T { return static_cast<T>(static_cast<juce::int64>(v)); }
};

template <typename T>
struct DurationFromVarImpl<T, true> {
    auto operator()(juce::var const& v) -> T { return static_cast<T>(v); }
};

template <typename T, typename R, bool isFloatingPoint = std::is_floating_point<T>::value>
struct DurationToVarImpl {
    auto operator()(std::chrono::duration<T, R> const& d) -> juce::var
    {
        return juce::var { static_cast<juce::int64>(d.count()) };
    }
};

template <typename T, typename R>
struct DurationToVarImpl<T, R, true> {
    auto operator()(std::chrono::duration<T, R> const& d) -> juce::var { return juce::var { d.count() }; }
};
} // namespace detail

} // namespace mc

/// \internal
template <typename T, typename R>
struct juce::VariantConverter<std::chrono::duration<T, R>> {
    MC_NODISCARD static auto fromVar(juce::var const& v) -> std::chrono::duration<T, R>
    {
        return std::chrono::duration<T, R> { mc::detail::DurationFromVarImpl<T> {}(v) };
    }

    MC_NODISCARD static auto toVar(std::chrono::duration<T, R> const& d) -> juce::var
    {
        return mc::detail::DurationToVarImpl<T, R> {}(d);
    }
};
