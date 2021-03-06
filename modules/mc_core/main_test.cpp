#include "mc_core/mc_core.hpp"

#include "catch2/catch_session.hpp"

auto main(int const argc, char const* argv[]) -> int
{
    auto init = juce::ScopedJuceInitialiser_GUI {};
    return Catch::Session().run(argc, argv);
}
