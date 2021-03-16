#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"

#include <mc_gui_basics/mc_gui_basics.hpp>

TEST_CASE("gui_basics/widget: TextBoxSlider::TextBoxSlider()", "[gui_basics][widget]")
{
    mc::TextBoxSlider slider {};
    CHECK(slider.getName() == "");
}

TEST_CASE("gui_basics/widget: TextBoxSlider::TextBoxSlider(componentName)", "[gui_basics][widget]")
{
    mc::TextBoxSlider slider {"slider"};
    CHECK(slider.getName() == "slider");
}

TEST_CASE("gui_basics/widget: TextBoxSlider::setValue", "[gui_basics][widget]")
{
    mc::TextBoxSlider slider {};
    CHECK(slider.getValue() == Catch::Approx(1.0));

    slider.setValue(2.0);
    CHECK(slider.getValue() == Catch::Approx(2.0));

    // outside range should be clipped
    slider.setValue(12.0);
    CHECK(slider.getValue() == Catch::Approx(10.0));
    slider.setValue(-5.0);
    CHECK(slider.getValue() == Catch::Approx(0.0));
}

TEST_CASE("gui_basics/widget: TextBoxSlider::Range", "[gui_basics][widget]")
{
    mc::TextBoxSlider slider {};
    CHECK(slider.getRange().getStart() == Catch::Approx(0.0));
    CHECK(slider.getRange().getEnd() == Catch::Approx(10.0));
    CHECK(slider.getMinimum() == Catch::Approx(0.0));
    CHECK(slider.getMaximum() == Catch::Approx(10.0));
    CHECK(slider.getInterval() == Catch::Approx(0.1));

    slider.setRange({0.0, 4.0}, 0.01);
    CHECK(slider.getRange().getStart() == Catch::Approx(0.0));
    CHECK(slider.getRange().getEnd() == Catch::Approx(4.0));
    CHECK(slider.getMinimum() == Catch::Approx(0.0));
    CHECK(slider.getMaximum() == Catch::Approx(4.0));
    CHECK(slider.getInterval() == Catch::Approx(0.01));
}

TEST_CASE("gui_basics/widget: TextBoxSlider::doubleClickReturn", "[gui_basics][widget]")
{
    mc::TextBoxSlider slider {};
    CHECK(slider.isDoubleClickReturnEnabled());
    CHECK(slider.getDoubleClickReturnValue() == Catch::Approx(1.0));

    slider.setDoubleClickReturnValue(true, 5.0);
    CHECK(slider.isDoubleClickReturnEnabled());
    CHECK(slider.getDoubleClickReturnValue() == Catch::Approx(5.0));

    slider.setDoubleClickReturnValue(false, 1.0);
    CHECK_FALSE(slider.isDoubleClickReturnEnabled());
    CHECK(slider.getDoubleClickReturnValue() == Catch::Approx(1.0));
}

TEST_CASE("gui_basics/widget: TextBoxSlider::onValueChange", "[gui_basics][widget]")
{
    auto wasCalled = false;
    mc::TextBoxSlider slider {};
    slider.onValueChange = [&wasCalled] { wasCalled = true; };
    slider.setValue(2.0);
    CHECK(wasCalled);
}

TEST_CASE("gui_basics/widget: TextBoxSlider::justificationType", "[gui_basics][widget]")
{
    mc::TextBoxSlider slider {};
    CHECK(slider.getJustificationType() == juce::Justification::centred);

    slider.setJustificationType(juce::Justification::centredTop);
    CHECK(slider.getJustificationType() == juce::Justification::centredTop);

    slider.setJustificationType(juce::Justification::centred);
    CHECK(slider.getJustificationType() == juce::Justification::centred);
}

TEST_CASE("gui_basics/widget: TextBoxSlider::textBoxEditable", "[gui_basics][widget]")
{
    mc::TextBoxSlider slider {};
    CHECK(slider.isTextBoxEditable());

    slider.setTextBoxIsEditable(false);
    CHECK_FALSE(slider.isTextBoxEditable());

    slider.setTextBoxIsEditable(true);
    CHECK(slider.isTextBoxEditable());
}

TEST_CASE("gui_basics/widget: TextBoxSlider::getValueFromText", "[gui_basics][widget]")
{
    mc::TextBoxSlider slider {};
    CHECK(slider.getValueFromText("1.0") == Catch::Approx(1.0));
    CHECK(slider.getValueFromText("2.0") == Catch::Approx(2.0));
    CHECK(slider.getValueFromText("1.43") == Catch::Approx(1.43));

    slider.valueFromText = [](auto const& text) -> double
    {
        juce::ignoreUnused(text);
        return 1.0;
    };
    CHECK(slider.getValueFromText("1.0") == Catch::Approx(1.0));
    CHECK(slider.getValueFromText("2.0") == Catch::Approx(1.0));
    CHECK(slider.getValueFromText("1.43") == Catch::Approx(1.0));
}

TEST_CASE("gui_basics/widget: TextBoxSlider::getTextFromValue", "[gui_basics][widget]")
{
    mc::TextBoxSlider slider {};
    CHECK(slider.getTextFromValue(1.0) == "1.0");
    CHECK(slider.getTextFromValue(2.0) == "2.0");

    slider.textFromValue = [](auto value) -> juce::String
    {
        juce::ignoreUnused(value);
        return "test";
    };
    CHECK(slider.getTextFromValue(1.0) == "test");
    CHECK(slider.getTextFromValue(2.0) == "test");
}

namespace
{

struct TestListenerValueChanged : mc::TextBoxSlider::Listener
{
    bool wasCalled {false};
    boost::optional<double> value {};

    ~TestListenerValueChanged() override = default;
    auto textBoxSliderDragStarted(mc::TextBoxSlider* /*s*/) -> void override { }
    auto textBoxSliderDragEnded(mc::TextBoxSlider* /*s*/) -> void override { }
    auto textBoxSliderValueChanged(mc::TextBoxSlider* s) -> void override
    {
        wasCalled = true;
        value     = s->getValue();
    }
};

}  // namespace

TEST_CASE("gui_basics/widget: TextBoxSlider::Listener::textBoxSliderValueChanged", "[gui_basics][widget]")
{
    auto listener = TestListenerValueChanged {};
    auto slider   = mc::TextBoxSlider {};
    CHECK_FALSE(listener.wasCalled);
    CHECK_FALSE(listener.value.has_value());

    slider.addListener(&listener);
    slider.setValue(2.0);
    CHECK(listener.wasCalled);
    CHECK(listener.value.has_value());
    CHECK(listener.value.value() == 2.0);

    slider.setValue(3.0);
    CHECK(listener.wasCalled);
    CHECK(listener.value.has_value());
    CHECK(listener.value.value() == 3.0);

    listener.wasCalled = false;
    listener.value     = {};
    slider.removeListener(&listener);
    slider.setValue(3.0);
    CHECK_FALSE(listener.wasCalled);
    CHECK_FALSE(listener.value.has_value());
    CHECK(slider.getValue() == 3.0);
}
