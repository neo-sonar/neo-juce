#ifndef MODERN_CIRCUITS_JUCE_MODULES_ASSERT_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_ASSERT_HPP

/// Assert handler implementation. Forwards to standard assert.
#if not defined(MC_ASSERT_IMPL)
#define MC_ASSERT_IMPL(text, exp) jassert((text) && (exp))
#endif

/// Assert handler implementation.
#if not defined(MC_ASSERT)
#define MC_ASSERT(exp) MC_ASSERT_IMPL("", (exp))
#endif

/// Expects asserts on a failed precondition. Forwards to standard assert.
#if not defined(MC_EXPECTS)
#define MC_EXPECTS(exp)                            \
    do {                                           \
        if (!(exp)) {                              \
            MC_ASSERT_IMPL("precondition", (exp)); \
        }                                          \
    } while (false)
#endif

/// Expects asserts on a failed postcondition, using a gsl::final_action run at
/// the end of the scope. Forwards to standard assert.
#if not defined(MC_ENSURES)
#define MC_ENSURES(exp)
#endif

#endif // MODERN_CIRCUITS_JUCE_MODULES_ASSERT_HPP
