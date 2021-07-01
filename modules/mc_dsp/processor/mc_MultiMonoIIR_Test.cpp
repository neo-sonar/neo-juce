#include <mc_dsp/mc_dsp.hpp>

#include "catch2/catch_template_test_macros.hpp"

TEMPLATE_TEST_CASE("dsp/processor: MultiMonoIIR", "[dsp][processor]", float, double)
{
    auto filter         = mc::MultiMonoIIR<TestType> {};
    auto buffer         = mc::AudioBufferUtils::createNoiseBuffer<TestType>(2, 512);
    auto originalBuffer = buffer;
    auto ioBuffer       = juce::dsp::AudioBlock<TestType>(buffer);
    auto const context  = juce::dsp::ProcessContextReplacing<TestType>(ioBuffer);

    filter.prepare({44'100.0, uint32_t(512), uint32_t(2)});
    filter.setCoefficients(juce::IIRCoefficients::makeLowPass(44'100.0, 800.0));
    filter.reset();
    filter.process(context);

    CHECK_FALSE(mc::AudioBufferUtils::containsNANs(buffer));
    CHECK_FALSE(mc::AudioBufferUtils::containsINFs(buffer));
}
