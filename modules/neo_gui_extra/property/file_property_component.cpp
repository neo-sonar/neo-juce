namespace neo {
FilePropertyComponent::FilePropertyComponent(juce::Value const& value,
    juce::String const& name,
    juce::String title,
    juce::String pattern,
    bool selectDirectory)
    : ValuePropertyComponent { value, name }, _title { std::move(title) }, _pattern { std::move(pattern) }
{
    _container.browse.onClick = [this, selectDirectory] { browseForFile(selectDirectory); };
    _container.clear.onClick  = [this] { this->value().setValue(""); };

    addAndMakeVisible(_container);
}

void FilePropertyComponent::refresh() { _container.filename.setText(value().toString()); }

auto FilePropertyComponent::browseForFile(bool selectDirectory) -> void
{
    auto const dir          = juce::FileBrowserComponent::canSelectDirectories;
    auto const file         = juce::FileBrowserComponent::canSelectFiles;
    auto const chooserFlags = (selectDirectory ? dir : file) | juce::FileBrowserComponent::openMode;
    auto const callback     = [this](auto const&) { value().setValue(_chooser->getResult().getFullPathName()); };

    _chooser = std::make_unique<juce::FileChooser>(_title, juce::File(value().toString()), _pattern);
    _chooser->launchAsync(chooserFlags, callback);
}

FilePropertyComponent::Container::Container()
{
    addAndMakeVisible(filename);
    addAndMakeVisible(browse);
    addAndMakeVisible(clear);

    filename.setReadOnly(true);
}

void FilePropertyComponent::Container::resized()
{
    auto rc = getLocalBounds();
    clear.setBounds(rc.removeFromRight(rc.getHeight()));
    browse.setBounds(rc.removeFromRight(rc.getHeight()));
    rc.removeFromRight(3);
    filename.setBounds(rc);
}

} // namespace neo
