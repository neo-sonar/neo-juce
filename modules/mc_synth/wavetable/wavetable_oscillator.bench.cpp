#include <mc_synth/mc_synth.hpp>

#include <benchmark/benchmark.h>

template <typename T>
static auto makeBenchOscillator()
{
    auto table = mc::makeSineWavetable<T>(2048U);
    auto osc   = mc::WavetableOscillator<T> {};
    osc.load(table);
    osc.frequency(440);
    osc.prepare(44'100.0);
    return osc;
}

static auto WavetableOscillator_Float(benchmark::State& state) -> void
{
    auto osc = makeBenchOscillator<float>();
    while (state.KeepRunning()) { benchmark::DoNotOptimize(osc.processSample()); }
}

BENCHMARK(WavetableOscillator_Float);

static auto WavetableOscillator_Double(benchmark::State& state) -> void
{
    auto osc = makeBenchOscillator<double>();
    while (state.KeepRunning()) { benchmark::DoNotOptimize(osc.processSample()); }
}

BENCHMARK(WavetableOscillator_Double);
