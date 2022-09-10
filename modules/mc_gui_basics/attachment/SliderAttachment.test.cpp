#include <mc_gui_basics/mc_gui_basics.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("gui_basics/attachment: SliderValueTreeAttachment", "")
{
    auto const id = juce::Identifier { "value" };
    juce::UndoManager undoManager {};
    juce::ValueTree valueTree { "test" };
    mc::CachedAtomicFloat value { valueTree, id, &undoManager };
    value = 2.0F;

    juce::Slider slider { "slider" };
    mc::SliderValueTreeAttachment attachment { valueTree, id, slider, &undoManager };
    CHECK(slider.getValue() == Catch::Approx(2.0F));

    slider.setValue(3.0F, juce::sendNotificationSync);
    CHECK(value.get() == Catch::Approx(3.0F));
    CHECK(slider.getValue() == Catch::Approx(3.0F));

    slider.startedDragging();
    slider.setValue(3.1F, juce::sendNotificationSync);
    CHECK(value.get() == Catch::Approx(3.1F));
    CHECK(slider.getValue() == Catch::Approx(3.1F));

    slider.setValue(3.2F, juce::sendNotificationSync);
    CHECK(value.get() == Catch::Approx(3.2F));
    CHECK(slider.getValue() == Catch::Approx(3.2F));
    slider.stoppedDragging();
}
