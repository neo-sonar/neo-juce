//#include <mc_gui_basics/mc_gui_basics.hpp>
//
//#include "catch2/catch_approx.hpp"
//#include "catch2/catch_template_test_macros.hpp"

// TEST_CASE("gui_basics/attachment: LabelValueTreeAttachment", "[gui_basics][attachment]")
//{
//    auto um       = juce::UndoManager {};
//    auto metadata = mc::PluginMetadata {juce::Identifier {"test_plugin"}, juce::ValueTree("test_plugin")};
//    CHECK(metadata.HostDAW == juce::String {"Unknown"});
//
//    auto label      = juce::Label {"label"};
//    auto attachment = mc::LabelValueTreeAttachment<juce::String> {metadata.State, mc::ids::hostDAW, label, &um};
//    CHECK(label.getText() == metadata.HostDAW);
//
//    metadata.HostDAW = juce::String {"foo"};
//    CHECK(metadata.HostDAW == juce::String {"foo"});
//    CHECK(label.getText() == juce::String {"foo"});
//}