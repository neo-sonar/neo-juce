#include <mc_gui_basics/mc_gui_basics.hpp>

#include <catch2/catch.hpp>

TEST_CASE("gui_basics/attachment: SliderValueTreeAttachment", "")
{
    auto const id = juce::Identifier { "value" };
    juce::UndoManager undoManager {};
    juce::ValueTree valueTree { "test" };
    mc::CachedAtomicFloat value { valueTree, id, &undoManager };
    value = 2.0f;

    juce::Slider slider { "slider" };
    mc::SliderValueTreeAttachment attachment { valueTree, id, slider, &undoManager };
    CHECK(slider.getValue() == Approx(2.0f));

    slider.setValue(3.0f, juce::sendNotificationSync);
    CHECK(value.get() == Approx(3.0f));
    CHECK(slider.getValue() == Approx(3.0f));

    slider.startedDragging();
    slider.setValue(3.1f, juce::sendNotificationSync);
    CHECK(value.get() == Approx(3.1f));
    CHECK(slider.getValue() == Approx(3.1f));

    slider.setValue(3.2f, juce::sendNotificationSync);
    CHECK(value.get() == Approx(3.2f));
    CHECK(slider.getValue() == Approx(3.2f));
    slider.stoppedDragging();
}