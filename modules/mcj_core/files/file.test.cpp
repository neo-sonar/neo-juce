// SPDX-License-Identifier: BSL-1.0

#include <mcj_core/mcj_core.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("core/files: VariantConverter<juce::File>", "[core]")
{
    auto roundtrip = [](auto const& tc) -> bool {
        auto const var = juce::VariantConverter<juce::File>::toVar(tc);
        return tc == juce::VariantConverter<juce::File>::fromVar(var);
    };

    REQUIRE(roundtrip(juce::File {}));
    REQUIRE(roundtrip(juce::File { R"(C:\foo\bar\baz.txt)" }));
    REQUIRE(roundtrip(juce::File { "/foo/bar/baz.txt" }));
}
