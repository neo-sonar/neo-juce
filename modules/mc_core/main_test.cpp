#include "catch2/catch_all.hpp"

#include "mc_core/mc_core.hpp"

auto main(int const argc, char const* argv[]) -> int
{
    juce::initialiseJuce_GUI();
    auto result = Catch::Session().run(argc, argv);
    juce::shutdownJuce_GUI();
    return result;
}
