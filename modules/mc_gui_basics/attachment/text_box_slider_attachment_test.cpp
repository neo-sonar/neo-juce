#include <mc_gui_basics/mc_gui_basics.hpp>

#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("gui_basics/attachment: TextBoxSliderValueTreeAttachment", "[gui_basics][attachment]")
{
    auto const id    = juce::Identifier {"value"};
    auto undoManager = juce::UndoManager {};
    auto valueTree   = juce::ValueTree {"test"};

    mc::CachedAtomicFloat value {valueTree, id, &undoManager};
    value = 2.0f;

    auto slider     = mc::TextBoxSlider {"slider"};
    auto attachment = mc::TextBoxSliderValueTreeAttachment {valueTree, id, slider, &undoManager};
    CHECK(slider.getValue() == Catch::Approx(2.0f));

    slider.setValue(3.0f, juce::sendNotificationSync);
    CHECK(value.get() == Catch::Approx(3.0f));
    CHECK(slider.getValue() == Catch::Approx(3.0f));
}