#include <mc_gui_basics/mc_gui_basics.hpp>

#include "catch2/catch_test_macros.hpp"

TEST_CASE("gui_basics/attachment: LabelValueTreeAttachment", "[gui_basics][attachment]")
{
    auto const id  = juce::String { "test" };
    auto um        = juce::UndoManager {};
    auto valueTree = juce::ValueTree { "test_plugin" };
    valueTree.setProperty(id, "test", &um);

    auto label = juce::Label { "label", "label" };
    CHECK(label.getText() == juce::String { "label" });

    auto attachment = mc::LabelValueTreeAttachment<juce::String> { valueTree, id, label, &um };
    CHECK(label.getText() == juce::String { "test" });
}