#pragma once

namespace neo {
struct FilePropertyComponent final : ValuePropertyComponent {
    FilePropertyComponent(juce::Value const& value,
        juce::String const& name,
        juce::String title   = "Open",
        juce::String pattern = "*.*",
        bool selectDirectory = false);
    ~FilePropertyComponent() override = default;

    auto refresh() -> void override;

private:
    auto browseForFile(bool selectDirectory) -> void;

    struct Container final : Component {
        Container();
        ~Container() override = default;

        auto resized() -> void override;

        juce::TextEditor filename;
        juce::TextButton browse { "..." };
        juce::TextButton clear { "X" };
    };

    Container _container;

    juce::String _title;
    juce::String _pattern;

    std::unique_ptr<juce::FileChooser> _chooser;
};

} // namespace neo
