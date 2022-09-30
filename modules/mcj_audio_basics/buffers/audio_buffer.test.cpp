#include <mcj_audio_basics/mcj_audio_basics.hpp>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

TEMPLATE_TEST_CASE("audio_basics/buffers: channel(juce::AudioBuffer)", "[audio_basics]", float, double)
{
    using mc::channel;
    using std::as_const;
    auto numSamples = GENERATE(32, 143, 256, 512, 1111, 4096);
    auto buffer     = juce::AudioBuffer<TestType> { 2, numSamples };

    REQUIRE(channel(buffer, 0).size() == static_cast<std::size_t>(numSamples));
    REQUIRE(channel(buffer, 1).size() == static_cast<std::size_t>(numSamples));
    REQUIRE(channel(buffer, 0).data() == buffer.getWritePointer(0));
    REQUIRE(channel(buffer, 1).data() == buffer.getWritePointer(1));

    REQUIRE(channel(as_const(buffer), 0).size() == static_cast<std::size_t>(numSamples));
    REQUIRE(channel(as_const(buffer), 1).size() == static_cast<std::size_t>(numSamples));
    REQUIRE(channel(as_const(buffer), 0).data() == buffer.getReadPointer(0));
    REQUIRE(channel(as_const(buffer), 1).data() == buffer.getReadPointer(1));
}

TEMPLATE_TEST_CASE("audio_basics/buffers: toVector(juce::AudioBuffer)", "[audio_basics]", float, double)
{
    auto numSamples = GENERATE(32, 143, 256, 512, 1111, 4096);
    auto buffer     = juce::AudioBuffer<TestType> { 2, numSamples };
    auto vec        = mc::toVector(buffer);

    REQUIRE(vec.size() == static_cast<std::size_t>(numSamples));
}
