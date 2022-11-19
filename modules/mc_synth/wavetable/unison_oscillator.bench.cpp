#include <mc_synth/mc_synth.hpp>

#include <benchmark/benchmark.h>

template <typename T>
static auto makeBenchUnisonOscillator(std::int64_t unison = 1)
{
    auto osc = mc::UnisonOscillator<T> {};
    osc.load(mc::makeSineWavetable<T>(2048U));
    osc.frequency(T(440));
    osc.detune(50);
    osc.unison(static_cast<int>(unison));
    osc.prepare(64);
    return osc;
    return osc;
}

template <typename T, size_t NumOsc>
static auto makeBenchUnisonOscillatorV2(std::int64_t unison = 1)
{
    auto osc = mc::UnisonOscillatorV2<T, NumOsc> {};
    osc.load(mc::makeSineWavetable<T>(2048U));
    osc.frequency(T(440));
    osc.detune(50);
    osc.unison(static_cast<int>(unison));
    osc.prepare(64);
    return osc;
    return osc;
}

static auto UnisonOscillator(benchmark::State& state) -> void
{
    auto osc = makeBenchUnisonOscillator<float>(state.range(0));
    while (state.KeepRunning()) { benchmark::DoNotOptimize(osc.processSample()); }
}

BENCHMARK(UnisonOscillator)->Arg(1)->Arg(2)->Arg(4)->Arg(6)->Arg(8);

static auto UnisonOscillatorV2(benchmark::State& state) -> void
{
    auto osc = makeBenchUnisonOscillatorV2<float, 8>(state.range(0));
    while (state.KeepRunning()) { benchmark::DoNotOptimize(osc.processSample()); }
}

BENCHMARK(UnisonOscillatorV2)->Arg(1)->Arg(2)->Arg(4)->Arg(6)->Arg(8);
