#include <neo_dsp/neo_dsp.hpp>

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

    [[nodiscard]] constexpr auto operator()(T actual) const -> decltype(juce::exactlyEqual(_expected, actual))
    {
        return juce::exactlyEqual(_expected, actual);
    }
};

TEST_CASE("dsp/algorithm: sizeAfterDownSample", "[dsp]")
{
    REQUIRE(neo::sizeAfterDownSample(512U, 1U) == 512U);
    REQUIRE(neo::sizeAfterDownSample(1024U, 1U) == 1024U);

    REQUIRE(neo::sizeAfterDownSample(512U, 2U) == 256U);
    REQUIRE(neo::sizeAfterDownSample(1024U, 2U) == 512U);
}

TEST_CASE("dsp/algorithm: downSample", "[dsp]")
{
    auto input = std::array<float, 8> {};
    std::ranges::fill(input, 1.0F);

    auto output = std::array<float, 4> {};
    REQUIRE(neo::downSample(input.data(), input.size(), output.data(), 2U) == 4U);
    REQUIRE(std::ranges::all_of(output, Equals<float> { 1.0F }));
}

TEST_CASE("dsp/algorithm: Averager", "[dsp]")
{
    using namespace neo;

    auto averager = Averager<float> { 2, 4 };
    REQUIRE(std::ranges::equal(averager.average(), std::array<float, 4> { 0.0F, 0.0F, 0.0F, 0.0F }));

    auto const ones = std::array<float, 4> { 1.0F, 1.0F, 1.0F, 1.0F };
    averager.push(ones);
    REQUIRE(std::ranges::equal(averager.average(), std::array<float, 4> { 0.5F, 0.5F, 0.5F, 0.5F }));

    averager.push(ones);
    REQUIRE(std::ranges::equal(averager.average(), ones));
}
