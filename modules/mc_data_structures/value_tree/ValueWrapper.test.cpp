#include <mc_data_structures/mc_data_structures.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("data_structures/value_tree: AtomicWrapper", "", int, float, double)
{
    constexpr auto iterations = 1'000;
    auto c                    = juce::ValueTree("CLIP");
    juce::CachedValue<mc::AtomicWrapper<TestType>> start;
    start.referTo(c, "start", nullptr);

    auto read = std::async(std::launch::async, [&] {
        for (int i = 0; i < iterations; ++i) { start = start.get() + TestType { 1 }; }
    });

    read.wait();
    CHECK(static_cast<TestType>(start.get()) == iterations);
}

TEMPLATE_TEST_CASE("data_structures/value_tree: ConstrainerWrapper", "", int, float, double)
{
    struct StartTimeConstrainer {
        static auto constrain(const TestType& v) -> TestType
        {
            return juce::Range<TestType>(static_cast<TestType>(0), static_cast<TestType>(42)).clipValue(v);
        }
    };

    struct CachedValueClip : public juce::ReferenceCountedObject {
        explicit CachedValueClip(juce::ValueTree const& v) : state { v }
        {
            CHECK(v.hasType("CLIP"));
            start.referTo(state, "start", nullptr);
        }

        juce::ValueTree state;
        juce::CachedValue<mc::ConstrainerWrapper<TestType, StartTimeConstrainer>> start;
    };

    juce::ValueTree clipState("CLIP");
    CachedValueClip c(clipState);

    c.start = 0;
    CHECK(c.start.get().value == 0);

    c.start = TestType { 10 };
    CHECK(c.start.get().value == TestType { 10 });

    c.start = TestType { 43 };
    CHECK(c.start.get().value == TestType { 42 });

    c.start = TestType { -1 };
    CHECK(c.start.get().value == TestType { 0 });
}
