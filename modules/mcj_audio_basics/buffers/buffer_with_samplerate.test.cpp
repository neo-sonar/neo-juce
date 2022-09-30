#include <mcj_audio_basics/mcj_audio_basics.hpp>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

TEMPLATE_TEST_CASE("audio_basics/buffers: toVector(BufferWithSampleRate)", "[audio_basics]", float, double)
{
    auto numSamples = GENERATE(32, 143, 256, 512, 1111, 4096);
    auto buffer     = mc::BufferWithSampleRate<TestType> { juce::AudioBuffer<TestType> { 1, numSamples } };
    auto vec        = mc::toVector(buffer);
    REQUIRE(vec.size() == static_cast<std::size_t>(numSamples));
}
