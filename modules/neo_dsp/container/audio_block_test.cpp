#include <neo_dsp/neo_dsp.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("dsp/container: channel(juce::dsp::AudioBlock)", "[dsp]", float, double)
{
    auto memory = juce::HeapBlock<char> {};
    auto block  = juce::dsp::AudioBlock<TestType> { memory, 2UL, 512UL };
    REQUIRE(neo::channel(block, 0).size() == 512UL);
    REQUIRE(neo::channel(block, 1).size() == 512UL);

    REQUIRE(neo::channel(block, 0).data() == block.getChannelPointer(0));
    REQUIRE(neo::channel(block, 1).data() == block.getChannelPointer(1));
}
