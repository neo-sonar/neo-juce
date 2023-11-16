#pragma once

auto juce::VariantConverter<juce::Colour>::fromVar(juce::var const& v) -> juce::Colour
{
    return juce::Colour::fromString(v.toString());
}

auto juce::VariantConverter<juce::Colour>::toVar(juce::Colour const& c) -> juce::var { return c.toString(); }
