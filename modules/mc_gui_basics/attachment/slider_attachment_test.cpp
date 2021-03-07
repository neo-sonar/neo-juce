//#include <mc_gui_basics/mc_gui_basics.hpp>
//
//#include "catch2/catch_approx.hpp"
//#include "catch2/catch_template_test_macros.hpp"

// TEST_CASE("gui_basics/attachment: SliderValueTreeAttachment", "[gui_basics][attachment]")
//{
//    auto undoManager = juce::UndoManager {};
//    auto macro       = mc::MacroModulator {juce::ValueTree(mc::ids::MACRO_MODULATOR), &undoManager};
//    CHECK(macro.value() == Catch::Approx(1.0f));
//
//    auto slider     = juce::Slider {"slider"};
//    auto attachment = mc::SliderValueTreeAttachment {macro.getValueTree(), mc::ids::value, slider, &undoManager};
//    CHECK(slider.getValue() == Catch::Approx(1.0f));
//
//    macro.setValue(2.0f);
//    CHECK(macro.value() == Catch::Approx(2.0f));
//    CHECK(slider.getValue() == Catch::Approx(2.0f));
//
//    slider.setValue(3.0f, juce::sendNotificationSync);
//    CHECK(macro.value() == Catch::Approx(3.0f));
//    CHECK(slider.getValue() == Catch::Approx(3.0f));
//
//    slider.startedDragging();
//    slider.setValue(3.1f, juce::sendNotificationSync);
//    CHECK(macro.value() == Catch::Approx(3.1f));
//    CHECK(slider.getValue() == Catch::Approx(3.1f));
//
//    slider.setValue(3.2f, juce::sendNotificationSync);
//    CHECK(macro.value() == Catch::Approx(3.2f));
//    CHECK(slider.getValue() == Catch::Approx(3.2f));
//    slider.stoppedDragging();
//}
//