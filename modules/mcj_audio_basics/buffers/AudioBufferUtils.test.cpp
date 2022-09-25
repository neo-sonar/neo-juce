#include <mcj_audio_basics/mcj_audio_basics.hpp>

#include <catch2/catch_template_test_macros.hpp>

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
