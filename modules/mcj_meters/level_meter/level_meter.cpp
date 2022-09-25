namespace mc {

LevelMeter::LevelMeter(MeterFlags type) : _meterType(type)
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

LevelMeter::~LevelMeter() { stopTimer(); }

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
    juce::Graphics::ScopedSaveState const saved(g);

    const juce::Rectangle<float> bounds = getLocalBounds().toFloat();
    int const numChannels               = _source != nullptr ? _source->getNumChannels() : 1;
    if (_useBackgroundImage) {
        // This seems to only speed up, if you use complex drawings on the background. For
        // "normal" vector graphics the image approach seems actually slower
        if (_backgroundNeedsRepaint) {
            _backgroundImage = juce::Image(juce::Image::ARGB, getWidth(), getHeight(), true);
            juce::Graphics backGraphics(_backgroundImage);
            _lmLookAndFeel->drawBackground(backGraphics, _meterType, bounds);
            _lmLookAndFeel->drawMeterBarsBackground(backGraphics, _meterType, bounds, numChannels, _fixedNumChannels);
            _backgroundNeedsRepaint = false;
        }
        g.drawImageAt(_backgroundImage, 0, 0);
        _lmLookAndFeel->drawMeterBars(g, _meterType, bounds, _source, _fixedNumChannels, _selectedChannel);
    } else {
        _lmLookAndFeel->drawBackground(g, _meterType, bounds);
        _lmLookAndFeel->drawMeterBarsBackground(g, _meterType, bounds, numChannels, _fixedNumChannels);
        _lmLookAndFeel->drawMeterBars(g, _meterType, bounds, _source, _fixedNumChannels, _selectedChannel);
    }

    if (_source != nullptr) { _source->decayIfNeeded(); }
}

void LevelMeter::resized()
{
    _lmLookAndFeel->updateMeterGradients();
    _backgroundNeedsRepaint = true;
}

void LevelMeter::visibilityChanged() { _backgroundNeedsRepaint = true; }

void LevelMeter::timerCallback()
{
    if (((_source != nullptr) && _source->checkNewDataFlag()) || _backgroundNeedsRepaint) {
        if (_source != nullptr) { _source->resetNewDataFlag(); }

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

void LevelMeter::mouseDown(const juce::MouseEvent& event)
{
    if (_source == nullptr) { return; }

    const juce::Rectangle<float> innerBounds
        = _lmLookAndFeel->getMeterInnerBounds(getLocalBounds().toFloat(), _meterType);
    if (event.mods.isLeftButtonDown()) {
        auto channel = _lmLookAndFeel->hitTestClipIndicator(event.getPosition(), _meterType, innerBounds, _source);
        if (channel >= 0) {
            _listeners.call(&LevelMeter::Listener::clipLightClicked, this, channel, event.mods);
            if (onClipLightClicked) { onClipLightClicked(*this, channel, event.mods); }
        }

        channel = _lmLookAndFeel->hitTestMaxNumber(event.getPosition(), _meterType, innerBounds, _source);
        if (channel >= 0) {
            _listeners.call(&LevelMeter::Listener::maxLevelClicked, this, channel, event.mods);
            if (onMaxLevelClicked) { onMaxLevelClicked(*this, channel, event.mods); }
        }
    }
}

void LevelMeter::addListener(LevelMeter::Listener* listener) { _listeners.add(listener); }

void LevelMeter::removeListener(LevelMeter::Listener* listener) { _listeners.remove(listener); }

void LevelMeter::parentHierarchyChanged() { lookAndFeelChanged(); }

void LevelMeter::lookAndFeelChanged()
{
    if (auto* lnf = dynamic_cast<LookAndFeelMethods*>(&getLookAndFeel())) {
        _lmLookAndFeel = lnf;
        return;
    }
}

} // namespace mc
