#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"

#include <mc_gui_basics/mc_gui_basics.hpp>

TEST_CASE("gui_basics/widget: BipolarFilter::BipolarFilter()", "[gui_basics][widget]")
{
    mc::BipolarFilter filter {};
    CHECK(filter.getName() == "");
}

TEST_CASE("gui_basics/widget: BipolarFilter::BipolarFilter(componentName)", "[gui_basics][widget]")
{
    mc::BipolarFilter filter {"filter"};
    CHECK(filter.getName() == "filter");
}

TEST_CASE("gui_basics/widget: BipolarFilter::setValue", "[gui_basics][widget]")
{
    mc::BipolarFilter filter {};
    CHECK(filter.getValue() == Catch::Approx(0.0));

    filter.setValue(0.5);
    CHECK(filter.getValue() == Catch::Approx(0.5));

    // outside range should be clipped
    filter.setValue(12.0);
    CHECK(filter.getValue() == Catch::Approx(1.0));
    filter.setValue(-5.0);
    CHECK(filter.getValue() == Catch::Approx(-1.0));
}

TEST_CASE("gui_basics/widget: BipolarFilter::doubleClickReturn", "[gui_basics][widget]")
{
    mc::BipolarFilter filter {};
    CHECK(filter.isDoubleClickReturnEnabled());
    CHECK(filter.getDoubleClickReturnValue() == Catch::Approx(0.0));

    filter.setDoubleClickReturnValue(true, 0.5);
    CHECK(filter.isDoubleClickReturnEnabled());
    CHECK(filter.getDoubleClickReturnValue() == Catch::Approx(0.5));

    filter.setDoubleClickReturnValue(false, 1.0);
    CHECK_FALSE(filter.isDoubleClickReturnEnabled());
    CHECK(filter.getDoubleClickReturnValue() == Catch::Approx(1.0));
}

namespace
{

struct TestListenerValueChanged : mc::BipolarFilter::Listener
{

    TestListenerValueChanged()           = default;
    ~TestListenerValueChanged() override = default;

    TestListenerValueChanged(const TestListenerValueChanged& other) = delete;
    TestListenerValueChanged(TestListenerValueChanged&& other)      = delete;
    auto operator=(const TestListenerValueChanged& rhs) -> TestListenerValueChanged& = delete;
    auto operator=(TestListenerValueChanged&& rhs) -> TestListenerValueChanged& = delete;

    auto bipolarFilterDragStarted(mc::BipolarFilter* /*s*/) -> void override { }
    auto bipolarFilterDragEnded(mc::BipolarFilter* /*s*/) -> void override { }
    auto bipolarFilterValueChanged(mc::BipolarFilter* s) -> void override
    {
        wasCalled = true;
        value     = s->getValue();
    }

    bool wasCalled {false};
    boost::optional<double> value {};
};

}  // namespace

TEST_CASE("gui_basics/widget: BipolarFilter::Listener::textBoxSliderValueChanged", "[gui_basics][widget]")
{
    auto listener = TestListenerValueChanged {};
    mc::BipolarFilter filter {};
    CHECK_FALSE(listener.wasCalled);
    CHECK_FALSE(listener.value.has_value());

    filter.addListener(&listener);
    filter.setValue(-0.25);
    CHECK(listener.wasCalled);
    CHECK(listener.value.has_value());
    CHECK(listener.value.value() == -0.25);

    filter.setValue(0.5);
    CHECK(listener.wasCalled);
    CHECK(listener.value.has_value());
    CHECK(listener.value.value() == 0.5);

    listener.wasCalled = false;
    listener.value     = {};
    filter.removeListener(&listener);
    filter.setValue(0.25);
    CHECK_FALSE(listener.wasCalled);
    CHECK_FALSE(listener.value.has_value());
    CHECK(filter.getValue() == 0.25);
}

//
// TEST_CASE("gui_basics/widget: BipolarFilter::Range", "[gui_basics][widget]")
//{
//    mc::BipolarFilter filter {};
//    CHECK(filter.getRange().getStart() == Catch::Approx(0.0));
//    CHECK(filter.getRange().getEnd() == Catch::Approx(10.0));
//    CHECK(filter.getMinimum() == Catch::Approx(0.0));
//    CHECK(filter.getMaximum() == Catch::Approx(10.0));
//    CHECK(filter.getInterval() == Catch::Approx(0.1));
//
//    filter.setRange({0.0, 4.0}, 0.01);
//    CHECK(filter.getRange().getStart() == Catch::Approx(0.0));
//    CHECK(filter.getRange().getEnd() == Catch::Approx(4.0));
//    CHECK(filter.getMinimum() == Catch::Approx(0.0));
//    CHECK(filter.getMaximum() == Catch::Approx(4.0));
//    CHECK(filter.getInterval() == Catch::Approx(0.01));
//}
//
//
// TEST_CASE("gui_basics/widget: BipolarFilter::onValueChange", "[gui_basics][widget]")
//{
//    auto wasCalled = false;
//    mc::BipolarFilter filter {};
//    filter.onValueChange = [&wasCalled] { wasCalled = true; };
//    filter.setValue(2.0);
//    CHECK(wasCalled);
//}