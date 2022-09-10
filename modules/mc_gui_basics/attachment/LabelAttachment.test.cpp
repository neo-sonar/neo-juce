#include <mc_gui_basics/mc_gui_basics.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("gui_basics/attachment: LabelValueTreeAttachment", "")
{
    auto const id = juce::String { "test" };
    juce::UndoManager um {};
    juce::ValueTree valueTree { "test_plugin" };
    valueTree.setProperty(id, "test", &um);

    juce::Label label { "label", "label" };
    REQUIRE(label.getText() == juce::String { "label" });

    mc::LabelValueTreeAttachment<juce::String> attachment { valueTree, id, label, &um };
    REQUIRE(label.getText() == juce::String { "test" });
}
