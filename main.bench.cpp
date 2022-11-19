#include <benchmark/benchmark.h>
#include <juce_events/juce_events.h>

auto main(int argc, char* argv[]) -> int
{
    auto init = juce::ScopedJuceInitialiser_GUI {};
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();
    return 0;
}
