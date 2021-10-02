#include <mc_gui_basics/mc_gui_basics.hpp>

#include <catch2/catch.hpp>

TEST_CASE("gui_basics/attachment: TextBoxSliderValueTreeAttachment", "[gui_basics][attachment]")
{
    juce::Identifier const id { "value" };
    juce::UndoManager undoManager {};
    juce::ValueTree valueTree { "test" };

    mc::CachedAtomicFloat value { valueTree, id, &undoManager };
    value = 2.0f;

    mc::TextBoxSlider slider { "slider" };
    mc::TextBoxSliderValueTreeAttachment attachment { valueTree, id, slider, &undoManager };
    CHECK(slider.getValue() == Approx(2.0f));

    slider.setValue(3.0f, juce::sendNotificationSync);
    CHECK(value.get() == Approx(3.0f));
    CHECK(slider.getValue() == Approx(3.0f));
}