#include <mcj_data_structures/mcj_data_structures.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("data_structures/value_tree: ConstrainerWrapper", "[data_structures]", int, float, double)
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
            REQUIRE(v.hasType("CLIP"));
            start.referTo(state, "start", nullptr);
        }

        juce::ValueTree state;
        juce::CachedValue<mc::ConstrainerWrapper<TestType, StartTimeConstrainer>> start;
    };

    juce::ValueTree const clipState("CLIP");
    CachedValueClip c(clipState);

    c.start = 0;
    REQUIRE(c.start.get().value == 0);

    c.start = TestType { 10 };
    REQUIRE(c.start.get().value == TestType { 10 });

    c.start = TestType { 43 };
    REQUIRE(c.start.get().value == TestType { 42 });

    c.start = TestType { -1 };
    REQUIRE(c.start.get().value == TestType { 0 });
}
