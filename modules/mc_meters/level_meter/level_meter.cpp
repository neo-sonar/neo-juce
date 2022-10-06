namespace mc {

LevelMeter::LevelMeter(MeterFlags type) : _meterType { type }
{
    lookAndFeelChanged();

    onMaxLevelClicked = [](mc::LevelMeter& meter, int channel, juce::ModifierKeys mods) {
        // default clear all indicators. Overwrite this lambda to change the behaviour
        meter.clearMaxLevelDisplay();
        meter.clearClipIndicator();
        (void)channel;
        (void)mods;
    };

    onClipLightClicked = [](mc::LevelMeter& meter, int channel, juce::ModifierKeys mods) {
        // default clear all indicators. Overwrite this lambda to change the behaviour
        meter.clearMaxLevelDisplay();
        meter.clearClipIndicator();
        (void)channel;
        (void)mods;
    };

    startTimerHz(_refreshRate);
}

void LevelMeter::setMeterFlags(MeterFlags type) { _meterType = type; }

void LevelMeter::setMeterSource(LevelMeterSource* src)
{
    _source = src;
    repaint();
}

void LevelMeter::setSelectedChannel(int c) { _selectedChannel = c; }

void LevelMeter::setFixedNumChannels(int numChannels) { _fixedNumChannels = numChannels; }

void LevelMeter::setRefreshRateHz(int newRefreshRate)
{
    _refreshRate = newRefreshRate;
    startTimerHz(_refreshRate);
}

void LevelMeter::paint(juce::Graphics& g)
{
    auto const saved       = juce::Graphics::ScopedSaveState { g };
    auto const bounds      = getLocalBounds().toFloat();
    auto const numChannels = _source != nullptr ? _source->numChannels() : 1;
    _lnf->drawBackground(g, _meterType, bounds);
    _lnf->drawMeterBarsBackground(g, _meterType, bounds, numChannels, _fixedNumChannels);
    _lnf->drawMeterBars(g, _meterType, bounds, _source, _fixedNumChannels, _selectedChannel);
    if (_source != nullptr) { _source->decayIfNeeded(); }
}

void LevelMeter::resized() { _lnf->updateMeterGradients(); }

void LevelMeter::timerCallback()
{
    if (_source == nullptr) { return; }
    if (_source->checkNewDataFlag()) {
        _source->resetNewDataFlag();
        repaint();
    }
}

void LevelMeter::clearClipIndicator(int channel)
{
    if (_source == nullptr) { return; }

    if (channel < 0) {
        _source->clearAllClipFlags();
    } else {
        _source->clearClipFlag(channel);
    }
}

void LevelMeter::clearMaxLevelDisplay(int channel)
{
    if (_source == nullptr) { return; }

    if (channel < 0) {
        _source->clearAllMaxNums();
    } else {
        _source->clearMaxNum(channel);
    }
}

void LevelMeter::mouseDown(juce::MouseEvent const& event)
{
    if (_source == nullptr) { return; }

    auto const bounds = _lnf->getMeterInnerBounds(getLocalBounds().toFloat(), _meterType);
    if (not event.mods.isLeftButtonDown()) { return; }

    auto channel = _lnf->hitTestClipIndicator(event.getPosition(), _meterType, bounds, _source);
    if (channel >= 0) {
        if (onClipLightClicked) { onClipLightClicked(*this, channel, event.mods); }
    }

    channel = _lnf->hitTestMaxNumber(event.getPosition(), _meterType, bounds, _source);
    if (channel >= 0) {
        if (onMaxLevelClicked) { onMaxLevelClicked(*this, channel, event.mods); }
    }
}

void LevelMeter::parentHierarchyChanged() { lookAndFeelChanged(); }

void LevelMeter::lookAndFeelChanged()
{
    if (auto* lnf = dynamic_cast<LookAndFeelMethods*>(&getLookAndFeel()); lnf != nullptr) { _lnf = lnf; }
}

} // namespace mc
