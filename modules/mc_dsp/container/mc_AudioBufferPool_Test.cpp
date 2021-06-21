#include <mc_dsp/mc_dsp.hpp>

#include "catch2/catch_template_test_macros.hpp"

// TODO: [tobi] Triggers ASAN
// TEMPLATE_TEST_CASE("dsp/container: AudioBufferPool", "[dsp][container]", float, double)
//{
//    auto pool = mc::AudioBufferPool {};
//    CHECK(pool.capacityInBytes() == 0);
//
//    pool.reserveBytes(1024);
//    CHECK(pool.capacityInBytes() == 1024);
//    CHECK(pool.sizeInBytes() == 0);
//
//    auto [b1, ok1] = pool.makeBuffer<TestType>(1, 32);
//    CHECK(ok1);
//    CHECK(b1.getNumChannels() == 1);
//    CHECK(b1.getNumSamples() == 32);
//    CHECK(pool.capacityInBytes() == 1024);
//    CHECK(pool.sizeInBytes() == 1 * 32 * sizeof(TestType));
//
//    auto [b2, ok2] = pool.makeBuffer<TestType>(2, 32);
//    CHECK(ok2);
//    CHECK(b2.getNumChannels() == 2);
//    CHECK(b2.getNumSamples() == 32);
//    CHECK(pool.capacityInBytes() == 1024);
//    CHECK(pool.sizeInBytes() == 3 * 32 * sizeof(TestType));
//
//    auto [b3, ok3] = pool.makeBuffer<TestType>(64, 32);
//    CHECK_FALSE(ok3);
//    CHECK(b3.getNumChannels() == 0);
//    CHECK(b3.getNumSamples() == 0);
//    CHECK(pool.capacityInBytes() == 1024);
//    CHECK(pool.sizeInBytes() == 3 * 32 * sizeof(TestType));
//
//    pool.reserveBytes(2048);
//    CHECK(pool.capacityInBytes() == 2048);
//    CHECK(pool.sizeInBytes() == 0);
//
//    auto [b4, ok4] = pool.makeBuffer<TestType>(1, 32);
//    CHECK(ok4);
//    CHECK(b4.getNumChannels() == 1);
//    CHECK(b4.getNumSamples() == 32);
//    CHECK(pool.capacityInBytes() == 2048);
//    CHECK(pool.sizeInBytes() == 1 * 32 * sizeof(TestType));
//}
