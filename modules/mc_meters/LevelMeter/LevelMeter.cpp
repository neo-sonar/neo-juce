
namespace mc {

LevelMeter::LevelMeter(MeterFlags type)
    : meterType_(type)
{
    lookAndFeelChanged();

    onMaxLevelClicked
        = [](mc::LevelMeter& meter, [[maybe_unused]] int channel, [[maybe_unused]] juce::ModifierKeys mods) {
              // default clear all indicators. Overwrite this lambda to change the behaviour
              meter.clearMaxLevelDisplay();
              meter.clearClipIndicator();
          };

    onClipLightClicked
        = [](mc::LevelMeter& meter, [[maybe_unused]] int channel, [[maybe_unused]] juce::ModifierKeys mods) {
              // default clear all indicators. Overwrite this lambda to change the behaviour
              meter.clearMaxLevelDisplay();
              meter.clearClipIndicator();
          };

    startTimerHz(refreshRate_);
}

LevelMeter::~LevelMeter() { stopTimer(); }

void LevelMeter::setMeterFlags(MeterFlags type) { meterType_ = type; }

void LevelMeter::setMeterSource(LevelMeterSource* src)
{
    source_ = src;
    repaint();
}

void LevelMeter::setSelectedChannel(int c) { selectedChannel_ = c; }

void LevelMeter::setFixedNumChannels(int numChannels) { fixedNumChannels_ = numChannels; }

void LevelMeter::setRefreshRateHz(int newRefreshRate)
{
    refreshRate_ = newRefreshRate;
    startTimerHz(refreshRate_);
}

void LevelMeter::paint(juce::Graphics& g)
{
    juce::Graphics::ScopedSaveState saved(g);

    const juce::Rectangle<float> bounds = getLocalBounds().toFloat();
    int numChannels                     = source_ != nullptr ? source_->getNumChannels() : 1;
    if (useBackgroundImage_) {
        // This seems to only speed up, if you use complex drawings on the background. For
        // "normal" vector graphics the image approach seems actually slower
        if (backgroundNeedsRepaint_) {
            backgroundImage_ = juce::Image(juce::Image::ARGB, getWidth(), getHeight(), true);
            juce::Graphics backGraphics(backgroundImage_);
            lmLookAndFeel_->drawBackground(backGraphics, meterType_, bounds);
            lmLookAndFeel_->drawMeterBarsBackground(backGraphics, meterType_, bounds, numChannels, fixedNumChannels_);
            backgroundNeedsRepaint_ = false;
        }
        g.drawImageAt(backgroundImage_, 0, 0);
        lmLookAndFeel_->drawMeterBars(g, meterType_, bounds, source_, fixedNumChannels_, selectedChannel_);
    } else {
        lmLookAndFeel_->drawBackground(g, meterType_, bounds);
        lmLookAndFeel_->drawMeterBarsBackground(g, meterType_, bounds, numChannels, fixedNumChannels_);
        lmLookAndFeel_->drawMeterBars(g, meterType_, bounds, source_, fixedNumChannels_, selectedChannel_);
    }

    if (source_ != nullptr) {
        source_->decayIfNeeded();
    }
}

void LevelMeter::resized()
{
    lmLookAndFeel_->updateMeterGradients();
    backgroundNeedsRepaint_ = true;
}

void LevelMeter::visibilityChanged() { backgroundNeedsRepaint_ = true; }

void LevelMeter::timerCallback()
{
    if (((source_ != nullptr) && source_->checkNewDataFlag()) || backgroundNeedsRepaint_) {
        if (source_ != nullptr) {
            source_->resetNewDataFlag();
        }

        repaint();
    }
}

void LevelMeter::clearClipIndicator(int channel)
{
    if (source_ == nullptr) {
        return;
    }

    if (channel < 0) {
        source_->clearAllClipFlags();
    } else {
        source_->clearClipFlag(channel);
    }
}

void LevelMeter::clearMaxLevelDisplay(int channel)
{
    if (source_ == nullptr) {
        return;
    }

    if (channel < 0) {
        source_->clearAllMaxNums();
    } else {
        source_->clearMaxNum(channel);
    }
}

void LevelMeter::mouseDown(const juce::MouseEvent& event)
{
    if (source_ == nullptr) {
        return;
    }

    const juce::Rectangle<float> innerBounds
        = lmLookAndFeel_->getMeterInnerBounds(getLocalBounds().toFloat(), meterType_);
    if (event.mods.isLeftButtonDown()) {
        auto channel = lmLookAndFeel_->hitTestClipIndicator(event.getPosition(), meterType_, innerBounds, source_);
        if (channel >= 0) {
            listeners_.call(&LevelMeter::Listener::clipLightClicked, this, channel, event.mods);
            if (onClipLightClicked) {
                onClipLightClicked(*this, channel, event.mods);
            }
        }

        channel = lmLookAndFeel_->hitTestMaxNumber(event.getPosition(), meterType_, innerBounds, source_);
        if (channel >= 0) {
            listeners_.call(&LevelMeter::Listener::maxLevelClicked, this, channel, event.mods);
            if (onMaxLevelClicked) {
                onMaxLevelClicked(*this, channel, event.mods);
            }
        }
    }
}

void LevelMeter::addListener(LevelMeter::Listener* listener) { listeners_.add(listener); }

void LevelMeter::removeListener(LevelMeter::Listener* listener) { listeners_.remove(listener); }

void LevelMeter::parentHierarchyChanged() { lookAndFeelChanged(); }

void LevelMeter::lookAndFeelChanged()
{
    if (auto* lnf = dynamic_cast<LookAndFeelMethods*>(&getLookAndFeel())) {
        lmLookAndFeel_ = lnf;
        return;
    }
}

} // namespace mc
