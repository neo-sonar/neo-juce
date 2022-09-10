#include <mc_dsp/mc_dsp.hpp>

#include <catch2/catch_template_test_macros.hpp>

template <typename T>
struct Equals {
private:
    T _expected;

public:
    constexpr explicit Equals(T expected) noexcept(std::is_nothrow_copy_constructible<T>::value)
        : _expected { expected }
    {
    }

    MC_NODISCARD constexpr auto operator()(T actual) const noexcept(noexcept(_expected == actual))
        -> decltype(_expected == actual)
    {
        return _expected == actual;
    }
};

TEST_CASE("dsp/algorithm: sizeAfterDownSample", "[dsp]")
{
    REQUIRE(mc::sizeAfterDownSample(512U, 1U) == 512U);
    REQUIRE(mc::sizeAfterDownSample(1024U, 1U) == 1024U);

    REQUIRE(mc::sizeAfterDownSample(512U, 2U) == 256U);
    REQUIRE(mc::sizeAfterDownSample(1024U, 2U) == 512U);
}

TEST_CASE("dsp/algorithm: downSample", "[dsp]")
{
    auto input = std::array<float, 8> {};
    std::fill(begin(input), end(input), 1.0F);

    auto output = std::array<float, 4> {};
    REQUIRE(mc::downSample(mc::data(input), mc::size(input), mc::data(output), 2U) == 4U);
    REQUIRE(std::all_of(begin(output), end(output), Equals<float> { 1.0F }));
}
