// SPDX-License-Identifier: BSL-1.0

#pragma once

template <typename T>
struct juce::VariantConverter<juce::Range<T>> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Range<T>
    {
        auto const splits = neo::strings::split(v.toString(), ':');
        auto const start  = neo::strings::toValue<T>(splits[0]);
        auto const end    = neo::strings::toValue<T>(splits[1]);
        return juce::Range<T> { start, end };
    }

    [[nodiscard]] static auto toVar(juce::Range<T> const& r) -> juce::var
    {
        return neo::jformat("{}:{}", r.getStart(), r.getEnd());
    }
};
