#include <mc_synth/mc_synth.hpp>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

TEMPLATE_TEST_CASE("synth/wavetable: makeSineWavetable", "[synth]", float, double) // NOLINT
{
    using namespace mc;

    auto const size      = GENERATE(as<std::size_t> {}, 256, 512, 1024, 2048, 4096);
    auto const sineTable = makeSineWavetable<TestType>(size);

    REQUIRE(sineTable != nullptr);
    REQUIRE_FALSE(sineTable->empty());
    REQUIRE(sineTable->size() == size);
    REQUIRE(sineTable->period() == size);
}

TEMPLATE_TEST_CASE("synth/wavetable: loadWavetable", "[synth]", float) // NOLINT
{
    using namespace mc;

    auto stream     = std::make_unique<juce::MemoryInputStream>(nullptr, 0, false);
    auto const null = loadWavetable<TestType>(std::move(stream));
    REQUIRE(null == nullptr);
}
