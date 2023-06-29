#include <mc_synth/mc_synth.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

TEMPLATE_TEST_CASE("synth/wavetable: unisonDetuneForVoice", "[synth]", float, double) // NOLINT
{
    using namespace mc;
    using T = TestType;

    REQUIRE(unisonDetuneForVoice<T>(1, 0) == T { 0 });

    auto voices = GENERATE(2, 3, 4, 5, 6, 7, 8);
    REQUIRE(unisonDetuneForVoice<T>(voices, 0) == Catch::Approx(T { -1 }));
    REQUIRE(unisonDetuneForVoice<T>(voices, voices - 1) == Catch::Approx(T { 1 }));

    // auto osc = mc::UnisonWavetableOsc<float, 16> {};
    // juce::ignoreUnused(osc);
}

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

TEST_CASE("synth/wavetable: WavetableOscillator", "[synth]") // NOLINT
{
    using namespace mc;

    auto osc = WavetableOscillator<float> {};
    REQUIRE(osc.processSample() == 0.0F);
}

TEMPLATE_TEST_CASE("synth/wavetable: WavetableOscillator(Sine)", "[synth]", float, double) // NOLINT
{
    using namespace mc;
    using T = TestType;

    auto renderTableToAudioBuffer = [](auto table, int length, T freq) {
        auto osc = WavetableOscillator<T> {};
        osc.load(table);
        osc.frequency(freq);
        osc.prepare(static_cast<T>(length));

        auto output = juce::AudioBuffer<T> { 1, length };
        auto* out   = output.getWritePointer(0);
        for (auto i { 0 }; i < output.getNumSamples(); ++i) { out[i] = osc.processSample(); }
        return output;
    };

    auto rmsErrorInDecibels = [](auto const& lhs, auto const& rhs) {
        return juce::Decibels::gainToDecibels(rmsError(channel(lhs, 0), channel(rhs, 0)));
    };

    auto frequency = GENERATE(T(30), T(440), T(880));
    auto length    = GENERATE(44'100, 48'000, 96'000);

    auto const buffer2048  = renderTableToAudioBuffer(makeSineWavetable<T>(2048U), length, frequency);
    auto const buffer4096  = renderTableToAudioBuffer(makeSineWavetable<T>(4096U), length, frequency);
    auto const buffer8192  = renderTableToAudioBuffer(makeSineWavetable<T>(8192U), length, frequency);
    auto const buffer16384 = renderTableToAudioBuffer(makeSineWavetable<T>(16384U), length, frequency);

    REQUIRE(rmsErrorInDecibels(buffer2048, buffer16384) < T(-50));
    REQUIRE(rmsErrorInDecibels(buffer4096, buffer16384) < T(-50));
    REQUIRE(rmsErrorInDecibels(buffer8192, buffer16384) < T(-50));
}
