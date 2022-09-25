#include <mcj_data_structures/mcj_data_structures.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("data_structures/values: AtomicWrapper", "[data_structures]", int, float, double)
{
    constexpr auto iterations = 1'000;
    auto c                    = juce::ValueTree("CLIP");
    juce::CachedValue<mc::AtomicWrapper<TestType>> start;
    start.referTo(c, "start", nullptr);

    auto read = std::async(std::launch::async, [&] {
        for (int i = 0; i < iterations; ++i) { start = start.get() + TestType { 1 }; }
    });

    read.wait();
    REQUIRE(static_cast<TestType>(start.get()) == iterations);
}
