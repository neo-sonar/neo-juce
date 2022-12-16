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
}

template <typename T, size_t NumOsc>
static auto makeBenchUnisonWavetableOsc(std::int64_t unison = 1)
{
    auto osc = mc::UnisonWavetableOsc<T, NumOsc> {};
    osc.load(mc::makeSineWavetable<T>(2048U));
    osc.frequency(T(440));
    osc.detune(50);
    osc.unison(static_cast<int>(unison));
    osc.prepare(64);
    return osc;
}

static auto unisonOscillator(benchmark::State& state) -> void
{
    auto osc = makeBenchUnisonOscillator<float>(state.range(0));
    while (state.KeepRunning()) { benchmark::DoNotOptimize(osc.processSample()); }
}

BENCHMARK(unisonOscillator)->Arg(1)->Arg(2)->Arg(4)->Arg(6)->Arg(8);

static auto unisonWavetableOsc(benchmark::State& state) -> void
{
    auto osc = makeBenchUnisonWavetableOsc<float, 8>(state.range(0));
    while (state.KeepRunning()) { benchmark::DoNotOptimize(osc.processSample()); }
}

BENCHMARK(unisonWavetableOsc)->Arg(1)->Arg(2)->Arg(4)->Arg(6)->Arg(8);
