#include <mc_dsp/mc_dsp.hpp>

#include <catch2/catch_template_test_macros.hpp>

// TODO: [tobi] Triggers ASAN
// TEMPLATE_TEST_CASE("dsp/container: AudioBufferPool", "", float, double)
//{
//    auto pool = mc::AudioBufferPool {};
//    REQUIRE(pool.capacityInBytes() == 0);
//
//    pool.reserveBytes(1024);
//    REQUIRE(pool.capacityInBytes() == 1024);
//    REQUIRE(pool.sizeInBytes() == 0);
//
//    auto [b1, ok1] = pool.makeBuffer<TestType>(1, 32);
//    REQUIRE(ok1);
//    REQUIRE(b1.getNumChannels() == 1);
//    REQUIRE(b1.getNumSamples() == 32);
//    REQUIRE(pool.capacityInBytes() == 1024);
//    REQUIRE(pool.sizeInBytes() == 1 * 32 * sizeof(TestType));
//
//    auto [b2, ok2] = pool.makeBuffer<TestType>(2, 32);
//    REQUIRE(ok2);
//    REQUIRE(b2.getNumChannels() == 2);
//    REQUIRE(b2.getNumSamples() == 32);
//    REQUIRE(pool.capacityInBytes() == 1024);
//    REQUIRE(pool.sizeInBytes() == 3 * 32 * sizeof(TestType));
//
//    auto [b3, ok3] = pool.makeBuffer<TestType>(64, 32);
//    REQUIRE_FALSE(ok3);
//    REQUIRE(b3.getNumChannels() == 0);
//    REQUIRE(b3.getNumSamples() == 0);
//    REQUIRE(pool.capacityInBytes() == 1024);
//    REQUIRE(pool.sizeInBytes() == 3 * 32 * sizeof(TestType));
//
//    pool.reserveBytes(2048);
//    REQUIRE(pool.capacityInBytes() == 2048);
//    REQUIRE(pool.sizeInBytes() == 0);
//
//    auto [b4, ok4] = pool.makeBuffer<TestType>(1, 32);
//    REQUIRE(ok4);
//    REQUIRE(b4.getNumChannels() == 1);
//    REQUIRE(b4.getNumSamples() == 32);
//    REQUIRE(pool.capacityInBytes() == 2048);
//    REQUIRE(pool.sizeInBytes() == 1 * 32 * sizeof(TestType));
//}
