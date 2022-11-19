#include <mc_synth/mc_synth.hpp>

#include <benchmark/benchmark.h>

template <typename T>
static constexpr auto s1 = static_cast<T>(0.49);

template <typename T>
static auto makeSamples(std::size_t size, T start, T end)
{
    auto samples = mc::Vector<T>(size);
    auto rnd     = std::mt19937 { std::random_device {}() };
    auto dis     = std::uniform_real_distribution<T>(start, end);
    std::generate(samples.begin(), samples.end(), [&] { return dis(rnd); });
    return samples;
}

static auto HermiteInterpolation_Float(benchmark::State& state) -> void
{
    auto ip      = mc::HermiteInterpolation<float> {};
    auto samples = makeSamples<float>(64, -1, 1);
    while (state.KeepRunning()) {
        auto selected = mc::samplesForHermiteInterpolation<float>(samples, 3);
        benchmark::DoNotOptimize(ip(selected, s1<float>));
    }
}

BENCHMARK(HermiteInterpolation_Float);

static auto HermiteInterpolation_Double(benchmark::State& state) -> void
{
    auto ip      = mc::HermiteInterpolation<double> {};
    auto samples = makeSamples<double>(64, -1, 1);
    while (state.KeepRunning()) {
        auto selected = mc::samplesForHermiteInterpolation<double>(samples, 3);
        benchmark::DoNotOptimize(ip(selected, s1<double>));
    }
}

BENCHMARK(HermiteInterpolation_Double);
