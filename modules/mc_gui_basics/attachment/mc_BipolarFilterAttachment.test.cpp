#include <mc_gui_basics/mc_gui_basics.hpp>

#include <catch2/catch.hpp>

TEST_CASE("gui_basics/attachment: BipolarFilterValueTreeAttachment", "")
{
    juce::Identifier const id { "value" };
    juce::UndoManager undoManager {};
    juce::ValueTree valueTree { "test" };

    mc::CachedAtomicFloat value { valueTree, id, &undoManager };
    value = 0.5f;

    mc::BipolarFilter slider { "filter" };
    mc::BipolarFilterValueTreeAttachment attachment { valueTree, id, slider, &undoManager };
    CHECK(slider.getValue() == Approx(0.5f));

    slider.setValue(0.25f);
    CHECK(value.get() == Approx(0.25f));
    CHECK(slider.getValue() == Approx(0.25f));

    value = -0.5f;
    CHECK(value.get() == Approx(-0.5f));
    CHECK(slider.getValue() == Approx(-0.5f));
}