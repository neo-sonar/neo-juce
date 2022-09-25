// SPDX-License-Identifier: BSL-1.0
#include <mcj_core/mcj_core.hpp>

#include <catch2/catch_template_test_macros.hpp>

namespace {
struct SomeStruct {
    float x, y, z;
    int a, b;
};
} // namespace

TEMPLATE_TEST_CASE("core/container: Registry::Construct", "[core]", char, int, float, SomeStruct)
{
    SECTION("default")
    {
        auto reg = mc::Registry<TestType> {};
        REQUIRE(reg.size() == 0);
        REQUIRE(reg.capacity() == 0);
    }

    SECTION("reserve capacity")
    {
        auto reg = mc::Registry<TestType> { 1024 };
        REQUIRE(reg.size() == 0);
        REQUIRE(reg.capacity() == 1024);
    }
}

TEMPLATE_TEST_CASE("core/container: Registry::Append", "[core]", char, int, float, SomeStruct)
{
    auto reg      = mc::Registry<TestType> {};
    auto const t1 = reg.append({});
    REQUIRE(reg.size() == 1);
    auto const t2 = reg.append({});
    REQUIRE(reg.size() == 2);
    REQUIRE(t1 < t2);
}

TEMPLATE_TEST_CASE("core/container: Registry::Erase", "[core]", char, int, float, SomeStruct)
{
    auto reg      = mc::Registry<TestType> {};
    auto const t1 = reg.append({});
    auto const t2 = reg.append({});
    REQUIRE(reg.size() == 2);

    reg.erase(t1);
    REQUIRE(reg.size() == 1);

    reg.erase(t2);
    REQUIRE(reg.size() == 0);
}

TEMPLATE_TEST_CASE("core/container: Registry::capacity", "[core]", char, int, float, SomeStruct)
{
    auto reg = mc::Registry<TestType> {};
    REQUIRE(reg.capacity() == 0);
    auto const t1 = reg.append({});
    auto const t2 = reg.append({});
    auto const t3 = reg.append({});
    auto const t4 = reg.append({});
    REQUIRE(reg.capacity() >= 4);

    reg.erase(t1);
    REQUIRE(reg.capacity() >= 4);
    reg.erase(t2);
    reg.erase(t3);
    REQUIRE(reg.capacity() == 1);
    reg.erase(t4);
    REQUIRE(reg.capacity() == 1);
}

TEST_CASE("core/container: Registry::forEach", "[core]")
{
    auto reg = mc::Registry<std::function<int(int)>> {};
    auto t1  = reg.append([](auto x) -> int { return x; });
    REQUIRE(reg.size() == 1);

    SECTION("single functor")
    {
        auto sum = 0;
        reg.forEach([&sum](auto const& func) { sum += func(1); });
        REQUIRE(sum == 1);
    }

    SECTION("2 functors")
    {
        auto sum = 0;
        auto t2  = reg.append([](auto x) -> int { return x * 2; });
        reg.forEach([&sum](auto const& func) { sum += func(1); });
        REQUIRE(sum == 3);
        reg.erase(t2);
    }

    reg.erase(t1);
    SECTION("no functor")
    {
        auto sum = 0;
        reg.forEach([&sum](auto const& func) { sum += func(1); });
        REQUIRE(sum == 0);
    }
}

TEST_CASE("core/container: Registry::forID", "[core]")
{
    auto reg = mc::Registry<std::function<int(int)>> {};

    SECTION("ticket invalid")
    {
        auto const ticket = reg.append([](auto x) -> int { return x; });
        reg.erase(ticket);
        REQUIRE_FALSE(reg.forID(ticket, [](auto const&) {}));
    }

    SECTION("ticket valid")
    {
        auto sum          = 0;
        auto const ticket = reg.append([](auto x) -> int { return x; });
        REQUIRE(reg.forID(ticket, [&sum](auto const& func) { sum += func(1); }));
        REQUIRE(sum == 1);
    }
}
