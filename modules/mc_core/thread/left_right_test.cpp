#include <mc_core/mc_core.hpp>

#include <catch2/catch_test_macros.hpp>

#include <map>
#include <string>

TEST_CASE("core/thread: LeftRight - in-place construct", "[core][thread]")
{
    using lrstring = mc::LeftRight<std::string>;

    lrstring lrs(mc::InPlace, 3, '*');
    lrs.observe([](lrstring::const_reference str) { CHECK(str == "***"); });
}

TEST_CASE("core/thread: LeftRight - modify read modify read", "[core][thread]")
{
    using lrmap = mc::LeftRight<std::map<int, int>>;
    lrmap lrm;
    lrm.modify([](lrmap::reference map) noexcept { map[1] = 1; });

    int value = lrm.observe([](lrmap::const_reference map) { return map.find(1)->second; });
    CHECK(1 == value);

    lrm.modify([](lrmap::reference map) noexcept { map[2] = 2; });

    value = lrm.observe([](lrmap::const_reference map) { return map.find(2)->second; });
    CHECK(2 == value);
}

TEST_CASE("core/thread: LeftRight - distributed modify read modify read", "[core][thread]")
{
    using lrmap = mc::BasicLeftRight<std::map<int, int>, mc::DistributedAtomicReaderRegistry<4>>;
    lrmap lrm;
    lrm.modify([](lrmap::reference map) noexcept { map[1] = 1; });

    int value = lrm.observe([](lrmap::const_reference map) { return map.find(1)->second; });
    CHECK(1 == value);

    lrm.modify([](lrmap::reference map) noexcept { map[2] = 2; });

    value = lrm.observe([](lrmap::const_reference map) { return map.find(2)->second; });
    CHECK(2 == value);
}

TEST_CASE("core/thread: LeftRight - noexcept specs", "[core][thread]")
{
    using lrint = mc::LeftRight<int>;
    lrint lri {0};

    auto nullObserver         = [](lrint::const_reference i) { return i; };
    auto noexceptNullObserver = [](lrint::const_reference i) noexcept { return i; };

    CHECK(noexcept(lri.observe(noexceptNullObserver)));
    CHECK(!noexcept(lri.observe(nullObserver)));

    auto noexceptNullModifier = [](lrint::reference i) noexcept { return i; };

    CHECK(0 == lri.modify(noexceptNullModifier));

    // this doesn't and shouldn't compile because modify only exists for
    // functors that are declared noexcept
    // auto null_modifier = [](lrint::reference i){ return i; };
    // CHECK(0 == lri.modify(null_modifier));
}

/*
struct unsafe_reader_registry
{
    void arrive(){}; //missing required noexcept
    void depart(){}; //missing required noexcept
    bool empty() const { return true; } //missing required noexcept
};
// This shouldn't and doesn't compile because the functions on
// unsafe_reader_registry are not noexcept
template class mc::BasicLeftRight<int, unsafe_reader_registry>;
*/