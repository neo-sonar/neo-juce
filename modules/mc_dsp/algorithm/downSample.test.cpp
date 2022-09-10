#include <mc_dsp/mc_dsp.hpp>

#include <catch2/catch_template_test_macros.hpp>

template <typename T>
struct Equals {
private:
    T expected_;

public:
    constexpr explicit Equals(T expected) noexcept(std::is_nothrow_copy_constructible<T>::value)
        : expected_ { expected }
    {
    }

    MC_NODISCARD constexpr auto operator()(T actual) const noexcept(noexcept(expected_ == actual))
        -> decltype(expected_ == actual)
    {
        return expected_ == actual;
    }
};

TEST_CASE("dsp/algorithm: sizeAfterDownSample", "")
{
    REQUIRE(mc::sizeAfterDownSample(512U, 1U) == 512U);
    REQUIRE(mc::sizeAfterDownSample(1024U, 1U) == 1024U);

    REQUIRE(mc::sizeAfterDownSample(512U, 2U) == 256U);
    REQUIRE(mc::sizeAfterDownSample(1024U, 2U) == 512U);
}

TEST_CASE("dsp/algorithm: downSample", "")
{
    auto input = std::array<float, 8> {};
    std::fill(begin(input), end(input), 1.0f);

    auto output = std::array<float, 4> {};
    REQUIRE(mc::downSample(mc::data(input), mc::size(input), mc::data(output), 2U) == 4U);
    REQUIRE(std::all_of(begin(output), end(output), Equals<float> { 1.0f }));
}
