#include <mc_gui_basics/mc_gui_basics.hpp>

#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("gui_basics/attachment: SliderValueTreeAttachment", "[gui_basics][attachment]")
{
    auto const id    = juce::Identifier { "value" };
    auto undoManager = juce::UndoManager {};
    auto valueTree   = juce::ValueTree { "test" };
    auto value       = mc::CachedAtomicFloat { valueTree, id, &undoManager };
    value            = 2.0f;

    auto slider     = juce::Slider { "slider" };
    auto attachment = mc::SliderValueTreeAttachment { valueTree, id, slider, &undoManager };
    CHECK(slider.getValue() == Catch::Approx(2.0f));

    slider.setValue(3.0f, juce::sendNotificationSync);
    CHECK(value.get() == Catch::Approx(3.0f));
    CHECK(slider.getValue() == Catch::Approx(3.0f));

    slider.startedDragging();
    slider.setValue(3.1f, juce::sendNotificationSync);
    CHECK(value.get() == Catch::Approx(3.1f));
    CHECK(slider.getValue() == Catch::Approx(3.1f));

    slider.setValue(3.2f, juce::sendNotificationSync);
    CHECK(value.get() == Catch::Approx(3.2f));
    CHECK(slider.getValue() == Catch::Approx(3.2f));
    slider.stoppedDragging();
}
