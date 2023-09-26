#include <mc_audio_basics/mc_audio_basics.hpp>

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

TEMPLATE_TEST_CASE("audio_basics/buffers: AudioBufferUtils::sumToMono", "[audio_basics]", float, double)
{
    auto src = juce::AudioBuffer<TestType> { 2, 512 };
    auto dst = juce::AudioBuffer<TestType> { 1, 512 };

    mc::AudioBufferUtils::fill(src, TestType { 0.5 });
    mc::AudioBufferUtils::sumToMono(src, dst);
    REQUIRE(mc::AudioBufferUtils::allOf(dst, TestType { 0.5 }));
}

TEMPLATE_TEST_CASE("audio_basics/buffers: AudioBufferUtils::split", "[audio_basics]", float, double)
{
    auto src = juce::AudioBuffer<TestType> { 1, 512 };
    auto dst = juce::AudioBuffer<TestType> { 4, 512 };

    mc::AudioBufferUtils::fill(src, TestType { 2.0 });
    mc::AudioBufferUtils::split(src, dst);
    REQUIRE(mc::AudioBufferUtils::allOf(dst, TestType { 2.0 }));
}

TEMPLATE_TEST_CASE("audio_basics/buffers: AudioBufferUtils::containsNANs", "[audio_basics]", float, double)
{
    auto buffer = juce::AudioBuffer<TestType> { 2, 512 };
    mc::AudioBufferUtils::fill(buffer, TestType { 0.5 });
    REQUIRE_FALSE(mc::AudioBufferUtils::containsNANs(buffer));
}

TEMPLATE_TEST_CASE("audio_basics/buffers: AudioBufferUtils::containsINFs", "[audio_basics]", float, double)
{
    auto buffer = juce::AudioBuffer<TestType> { 2, 512 };
    mc::AudioBufferUtils::fill(buffer, TestType { 0.5 });
    REQUIRE_FALSE(mc::AudioBufferUtils::containsINFs(buffer));
}

TEMPLATE_TEST_CASE("audio_basics/buffers: AudioBufferUtils::equal", "[audio_basics]", float, double)
{
    SECTION("same buffer")
    {
        auto buffer = juce::AudioBuffer<TestType> { 2, 512 };
        mc::AudioBufferUtils::fill(buffer, TestType { 0.5 });
        REQUIRE(mc::AudioBufferUtils::equal(buffer, buffer));
    }
}

TEMPLATE_TEST_CASE("audio_basics/buffers: toVector(BufferWithSampleRate)", "[audio_basics]", float, double)
{
    auto numSamples = GENERATE(32, 143, 256, 512, 1111, 4096);
    auto buffer     = mc::BufferWithSampleRate<TestType> { juce::AudioBuffer<TestType> { 1, numSamples }, 44'100.0 };
    auto vec        = mc::toVector(buffer);
    REQUIRE(vec.size() == static_cast<std::size_t>(numSamples));
}
