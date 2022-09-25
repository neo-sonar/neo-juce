#include <mcj_dsp/mcj_dsp.hpp>

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

    [[nodiscard]] constexpr auto operator()(T actual) const noexcept(noexcept(_expected == actual))
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
    auto input = mc::Array<float, 8> {};
    ranges::fill(input, 1.0F);

    auto output = mc::Array<float, 4> {};
    REQUIRE(mc::downSample(mc::data(input), mc::size(input), mc::data(output), 2U) == 4U);
    REQUIRE(ranges::all_of(output, Equals<float> { 1.0F }));
}
