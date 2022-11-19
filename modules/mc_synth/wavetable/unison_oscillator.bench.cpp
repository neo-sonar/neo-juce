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

static auto UnisonOscillator_Float(benchmark::State& state) -> void
{
    auto osc = makeBenchUnisonOscillator<float>(state.range(0));
    while (state.KeepRunning()) { benchmark::DoNotOptimize(osc.processSample()); }
}

BENCHMARK(UnisonOscillator_Float)->Arg(1)->Arg(2)->Arg(4);

static auto UnisonOscillator_Double(benchmark::State& state) -> void
{
    auto osc = makeBenchUnisonOscillator<double>(state.range(0));
    while (state.KeepRunning()) { benchmark::DoNotOptimize(osc.processSample()); }
}

BENCHMARK(UnisonOscillator_Double)->Arg(1)->Arg(2)->Arg(4);
;