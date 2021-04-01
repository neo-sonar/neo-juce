
void setupDefaultMeterColours() override
{
    setColour(foleys::LevelMeter::lmTextColour, juce::Colours::lightgrey);
    setColour(foleys::LevelMeter::lmTextClipColour, juce::Colours::white);
    setColour(foleys::LevelMeter::lmTextDeactiveColour, juce::Colours::darkgrey);
    setColour(foleys::LevelMeter::lmTicksColour, juce::Colours::orange);
    setColour(foleys::LevelMeter::lmOutlineColour, juce::Colours::orange);
    setColour(foleys::LevelMeter::lmBackgroundColour, juce::Colour(0xff050a29));
    setColour(foleys::LevelMeter::lmBackgroundClipColour, juce::Colours::red);
    setColour(foleys::LevelMeter::lmMeterForegroundColour, juce::Colours::green);
    setColour(foleys::LevelMeter::lmMeterOutlineColour, juce::Colours::lightgrey);
    setColour(foleys::LevelMeter::lmMeterBackgroundColour, juce::Colours::darkgrey);
    setColour(foleys::LevelMeter::lmMeterMaxNormalColour, juce::Colours::lightgrey);
    setColour(foleys::LevelMeter::lmMeterMaxWarnColour, juce::Colours::orange);
    setColour(foleys::LevelMeter::lmMeterMaxOverColour, juce::Colours::darkred);
    setColour(foleys::LevelMeter::lmMeterGradientLowColour, juce::Colours::green);
    setColour(foleys::LevelMeter::lmMeterGradientMidColour, juce::Colours::lightgoldenrodyellow);
    setColour(foleys::LevelMeter::lmMeterGradientMaxColour, juce::Colours::red);
    setColour(foleys::LevelMeter::lmMeterReductionColour, juce::Colours::orange);
}

void updateMeterGradients() override
{
    horizontalGradient_.clearColours();
    verticalGradient_.clearColours();
}

[[nodiscard]] auto getMeterInnerBounds(juce::Rectangle<float> bounds, foleys::LevelMeter::MeterFlags meterType) const
    -> juce::Rectangle<float> override
{
    if ((meterType & foleys::LevelMeter::HasBorder) != 0)
    {
        const auto corner = std::min(bounds.getWidth(), bounds.getHeight()) * 0.01f;
        return bounds.reduced(3 + corner);
    }

    return bounds;
}

[[nodiscard]] auto getMeterBounds(juce::Rectangle<float> bounds, foleys::LevelMeter::MeterFlags meterType,
                                  int numChannels, int channel) const -> juce::Rectangle<float> override
{
    if ((meterType & foleys::LevelMeter::SingleChannel) != 0) { return bounds; }

    if ((meterType & foleys::LevelMeter::Horizontal) != 0)
    {
        const float h = bounds.getHeight() / numChannels;
        return bounds.withHeight(h).withY(bounds.getY() + channel * h);
    }

    const float w = bounds.getWidth() / numChannels;
    return bounds.withWidth(w).withX(bounds.getX() + channel * w);
}

/** Override this callback to define the placement of the actual meter bar. */
[[nodiscard]] auto getMeterBarBounds(juce::Rectangle<float> bounds, foleys::LevelMeter::MeterFlags meterType) const
    -> juce::Rectangle<float> override
{
    if ((meterType & foleys::LevelMeter::Minimal) != 0)
    {
        if ((meterType & foleys::LevelMeter::Horizontal) != 0)
        {
            const auto margin = bounds.getHeight() * 0.05f;
            const auto h      = bounds.getHeight() - 2.0f * margin;
            const auto left   = bounds.getX() + margin;
            const auto right  = bounds.getRight() - (4.0f * margin + h);
            return juce::Rectangle<float>(bounds.getX() + margin, bounds.getY() + margin, right - left, h);
        }

        const auto margin = bounds.getWidth() * 0.05f;
        const auto top    = bounds.getY() + 2.0f * margin + bounds.getWidth() * 0.5f;
        const auto bottom = (meterType & foleys::LevelMeter::MaxNumber) != 0
                                ? bounds.getBottom() - (3.0f * margin + (bounds.getWidth() - margin * 2.0f))
                                : bounds.getBottom() - margin;
        return juce::Rectangle<float>(bounds.getX() + margin, top, bounds.getWidth() - margin * 2.0f, bottom - top);
    }

    if ((meterType & foleys::LevelMeter::Vintage) != 0) { return bounds; }

    if ((meterType & foleys::LevelMeter::Horizontal) != 0)
    {
        const auto margin = bounds.getHeight() * 0.05f;
        const auto h      = bounds.getHeight() * 0.5f - 2.0f * margin;
        const auto left   = 60.0f + 3.0f * margin;
        const auto right  = bounds.getRight() - (4.0f * margin + h * 0.5f);
        return juce::Rectangle<float>(bounds.getX() + left, bounds.getY() + margin, right - left, h);
    }

    const auto margin = bounds.getWidth() * 0.05f;
    const auto w      = bounds.getWidth() * 0.45f;
    const auto top    = bounds.getY() + 2.0f * margin + w * 0.5f;
    const auto bottom = bounds.getBottom() - (2.0f * margin + 25.0f);
    return juce::Rectangle<float>(bounds.getX() + margin, top, w, bottom - top);
}

/** Override this callback to define the placement of the tickmarks.
 To disable this feature return an empty rectangle. */
[[nodiscard]] auto getMeterTickmarksBounds(juce::Rectangle<float> bounds,
                                           foleys::LevelMeter::MeterFlags meterType) const
    -> juce::Rectangle<float> override
{
    if ((meterType & foleys::LevelMeter::Minimal) != 0)
    {
        if ((meterType & foleys::LevelMeter::Horizontal) != 0)
        {
            return getMeterBarBounds(bounds, meterType).reduced(0.0, 2.0);
        }

        return getMeterBarBounds(bounds, meterType).reduced(2.0, 0.0);
    }

    if ((meterType & foleys::LevelMeter::Vintage) != 0) { return bounds; }

    if ((meterType & foleys::LevelMeter::Horizontal) != 0)
    {
        const auto margin = bounds.getHeight() * 0.05f;
        const auto h      = bounds.getHeight() * 0.5f - 2.0f * margin;
        const auto left   = 60.0f + 3.0f * margin;
        const auto right  = bounds.getRight() - (4.0f * margin + h * 0.5f);
        return juce::Rectangle<float>(bounds.getX() + left, bounds.getCentreY() + margin, right - left, h);
    }

    const auto margin = bounds.getWidth() * 0.05f;
    const auto w      = bounds.getWidth() * 0.45f;
    const auto top    = bounds.getY() + 2.0f * margin + w * 0.5f + 2.0f;
    const auto bottom = bounds.getBottom() - (2.0f * margin + 25.0f + 2.0f);
    return juce::Rectangle<float>(bounds.getCentreX(), top, w, bottom - top);
}

/** Override this callback to define the placement of the clip indicator light.
 To disable this feature return an empty rectangle. */
[[nodiscard]] auto getMeterClipIndicatorBounds(juce::Rectangle<float> bounds,
                                               foleys::LevelMeter::MeterFlags meterType) const
    -> juce::Rectangle<float> override
{
    if ((meterType & foleys::LevelMeter::Minimal) != 0)
    {
        if ((meterType & foleys::LevelMeter::Horizontal) != 0)
        {
            const auto margin = bounds.getHeight() * 0.05f;
            const auto h      = bounds.getHeight() - 2.0f * margin;
            return juce::Rectangle<float>(bounds.getRight() - (margin + h), bounds.getY() + margin, h, h);
        }

        const auto margin = bounds.getWidth() * 0.05f;
        const auto w      = bounds.getWidth() - margin * 2.0f;
        return juce::Rectangle<float>(bounds.getX() + margin, bounds.getY() + margin, w, w * 0.5f);
    }
    if ((meterType & foleys::LevelMeter::Vintage) != 0) { return bounds; }
    if ((meterType & foleys::LevelMeter::Horizontal) != 0)
    {
        const auto margin = bounds.getHeight() * 0.05f;
        const auto h      = bounds.getHeight() * 0.5f - 2.0f * margin;
        return juce::Rectangle<float>(bounds.getRight() - (margin + h * 0.5f), bounds.getY() + margin, h * 0.5f, h);
    }

    const auto margin = bounds.getWidth() * 0.05f;
    const auto w      = bounds.getWidth() * 0.45f;
    return juce::Rectangle<float>(bounds.getX() + margin, bounds.getY() + margin, w, w * 0.5f);
}

/** Override this callback to define the placement of the max level.
 To disable this feature return an empty rectangle. */
[[nodiscard]] auto getMeterMaxNumberBounds(juce::Rectangle<float> bounds,
                                           foleys::LevelMeter::MeterFlags meterType) const
    -> juce::Rectangle<float> override
{
    if ((meterType & foleys::LevelMeter::Minimal) != 0)
    {
        if ((meterType & foleys::LevelMeter::MaxNumber) != 0)
        {
            if ((meterType & foleys::LevelMeter::Horizontal) != 0)
            {
                const auto margin = bounds.getHeight() * 0.05f;
                const auto h      = bounds.getHeight() - 2.0f * margin;
                return juce::Rectangle<float>(bounds.getRight() - (margin + h), bounds.getY() + margin, h, h);
            }

            const auto margin = bounds.getWidth() * 0.05f;
            const auto w      = bounds.getWidth() - margin * 2.0f;
            const auto h      = w * 0.6f;
            return juce::Rectangle<float>(bounds.getX() + margin, bounds.getBottom() - (margin + h), w, h);
        }

        return juce::Rectangle<float>();
    }
    if ((meterType & foleys::LevelMeter::Vintage) != 0) { return bounds; }

    if ((meterType & foleys::LevelMeter::Horizontal) != 0)
    {
        const auto margin = bounds.getHeight() * 0.05f;
        return juce::Rectangle<float>(bounds.getX() + margin, bounds.getCentreY() + margin, 60,
                                      bounds.getHeight() * 0.5f - margin * 2.0f);
    }

    const auto margin = bounds.getWidth() * 0.05f;
    return juce::Rectangle<float>(bounds.getX() + margin, bounds.getBottom() - (margin + 25),
                                  bounds.getWidth() - 2 * margin, 25.0);
}

auto drawBackground(juce::Graphics& g, foleys::LevelMeter::MeterFlags meterType, juce::Rectangle<float> bounds)
    -> juce::Rectangle<float> override
{
    g.setColour(findColour(foleys::LevelMeter::lmBackgroundColour));
    if ((meterType & foleys::LevelMeter::HasBorder) != 0)
    {
        const auto corner = std::min(bounds.getWidth(), bounds.getHeight()) * 0.01f;
        g.fillRoundedRectangle(bounds, corner);
        g.setColour(findColour(foleys::LevelMeter::lmOutlineColour));
        g.drawRoundedRectangle(bounds.reduced(3), corner, 2);
        return bounds.reduced(3 + corner);
    }

    g.fillRect(bounds);
    return bounds;
}

void drawMeterBars(juce::Graphics& g, foleys::LevelMeter::MeterFlags meterType, juce::Rectangle<float> bounds,
                   const foleys::LevelMeterSource* source, int fixedNumChannels = -1, int selectedChannel = -1) override
{
    if (source == nullptr) { return; }

    const juce::Rectangle<float> innerBounds = getMeterInnerBounds(bounds, meterType);
    const int numChannels                    = source->getNumChannels();
    if ((meterType & foleys::LevelMeter::Minimal) != 0)
    {
        if ((meterType & foleys::LevelMeter::Horizontal) != 0)
        {
            const float height           = innerBounds.getHeight() / (2 * numChannels - 1);
            juce::Rectangle<float> meter = innerBounds.withHeight(height);
            for (int channel = 0; channel < numChannels; ++channel)
            {
                meter.setY(height * channel * 2);
                {
                    juce::Rectangle<float> meterBarBounds = getMeterBarBounds(meter, meterType);
                    drawMeterBar(g, meterType, meterBarBounds, source->getRMSLevel(channel),
                                 source->getMaxLevel(channel));
                    const float reduction = source->getReductionLevel(channel);
                    if (reduction < 1.0)
                    {
                        drawMeterReduction(g, meterType, meterBarBounds.withBottom(meterBarBounds.getCentreY()),
                                           reduction);
                    }
                }

                juce::Rectangle<float> clip = getMeterClipIndicatorBounds(meter, meterType);
                if (!clip.isEmpty()) { drawClipIndicator(g, meterType, clip, source->getClipFlag(channel)); }
                juce::Rectangle<float> maxNum = getMeterMaxNumberBounds(meter, meterType);

                if (!maxNum.isEmpty()) { drawMaxNumber(g, meterType, maxNum, source->getMaxOverallLevel(channel)); }

                if (channel < numChannels - 1)
                {
                    meter.setY(height * (channel * 2 + 1));
                    juce::Rectangle<float> ticks = getMeterTickmarksBounds(meter, meterType);
                    if (!ticks.isEmpty()) { drawTickMarks(g, meterType, ticks); }
                }
            }
        }
        else
        {
            const float width            = innerBounds.getWidth() / (2 * numChannels - 1);
            juce::Rectangle<float> meter = innerBounds.withWidth(width);
            for (int channel = 0; channel < numChannels; ++channel)
            {
                meter.setX(width * channel * 2);
                {
                    juce::Rectangle<float> meterBarBounds = getMeterBarBounds(meter, meterType);
                    drawMeterBar(g, meterType, getMeterBarBounds(meter, meterType), source->getRMSLevel(channel),
                                 source->getMaxLevel(channel));
                    const float reduction = source->getReductionLevel(channel);
                    if (reduction < 1.0)
                    {
                        drawMeterReduction(g, meterType, meterBarBounds.withLeft(meterBarBounds.getCentreX()),
                                           reduction);
                    }
                }
                juce::Rectangle<float> clip = getMeterClipIndicatorBounds(meter, meterType);
                if (!clip.isEmpty()) { drawClipIndicator(g, meterType, clip, source->getClipFlag(channel)); }
                juce::Rectangle<float> maxNum = getMeterMaxNumberBounds(
                    innerBounds.withWidth(innerBounds.getWidth() / numChannels)
                        .withX(innerBounds.getX() + channel * (innerBounds.getWidth() / numChannels)),
                    meterType);
                if (!maxNum.isEmpty()) { drawMaxNumber(g, meterType, maxNum, source->getMaxOverallLevel(channel)); }
                if (channel < numChannels - 1)
                {
                    meter.setX(width * (channel * 2 + 1));
                    juce::Rectangle<float> ticks = getMeterTickmarksBounds(meter, meterType);
                    if (!ticks.isEmpty()) { drawTickMarks(g, meterType, ticks); }
                }
            }
        }
    }
    else if ((meterType & foleys::LevelMeter::SingleChannel) != 0)
    {
        if (selectedChannel >= 0) { drawMeterChannel(g, meterType, innerBounds, source, selectedChannel); }
    }
    else
    {
        const int numDrawnChannels = fixedNumChannels < 0 ? numChannels : fixedNumChannels;
        for (int channel = 0; channel < numChannels; ++channel)
        {
            drawMeterChannel(g, meterType, getMeterBounds(innerBounds, meterType, numDrawnChannels, channel), source,
                             channel);
        }
    }
}

void drawMeterBarsBackground(juce::Graphics& g, foleys::LevelMeter::MeterFlags meterType, juce::Rectangle<float> bounds,
                             int numChannels, int fixedNumChannels) override
{
    const juce::Rectangle<float> innerBounds = getMeterInnerBounds(bounds, meterType);
    if ((meterType & foleys::LevelMeter::Minimal) != 0)
    {
        if ((meterType & foleys::LevelMeter::Horizontal) != 0)
        {
            const float height           = innerBounds.getHeight() / (2 * numChannels - 1);
            juce::Rectangle<float> meter = innerBounds.withHeight(height);
            for (int channel = 0; channel < numChannels; ++channel)
            {
                meter.setY(height * channel * 2);
                drawMeterBarBackground(g, meterType, getMeterBarBounds(meter, meterType));
                juce::Rectangle<float> clip = getMeterClipIndicatorBounds(meter, meterType);
                if (!clip.isEmpty()) { drawClipIndicatorBackground(g, meterType, clip); }
                if (channel < numChannels - 1)
                {
                    meter.setY(height * (channel * 2 + 1));
                    juce::Rectangle<float> ticks = getMeterTickmarksBounds(meter, meterType);
                    if (!ticks.isEmpty()) { drawTickMarks(g, meterType, ticks); }
                }
            }
        }
        else
        {
            const float width            = innerBounds.getWidth() / (2 * numChannels - 1);
            juce::Rectangle<float> meter = innerBounds.withWidth(width);
            for (int channel = 0; channel < numChannels; ++channel)
            {
                meter.setX(width * channel * 2);
                drawMeterBarBackground(g, meterType, getMeterBarBounds(meter, meterType));
                juce::Rectangle<float> clip = getMeterClipIndicatorBounds(meter, meterType);
                if (!clip.isEmpty()) { drawClipIndicatorBackground(g, meterType, clip); }
                if (channel < numChannels - 1)
                {
                    meter.setX(width * (channel * 2 + 1));
                    juce::Rectangle<float> ticks = getMeterTickmarksBounds(meter, meterType);
                    if (!ticks.isEmpty()) { drawTickMarks(g, meterType, ticks); }
                }
            }
        }
    }
    else if ((meterType & foleys::LevelMeter::SingleChannel) != 0)
    {
        drawMeterChannelBackground(g, meterType, innerBounds);
    }
    else
    {
        for (int channel = 0; channel < numChannels; ++channel)
        {
            drawMeterChannelBackground(
                g, meterType,
                getMeterBounds(innerBounds, meterType, fixedNumChannels < 0 ? numChannels : fixedNumChannels, channel));
        }
    }
}

void drawMeterChannel(juce::Graphics& g, foleys::LevelMeter::MeterFlags meterType, juce::Rectangle<float> bounds,
                      const foleys::LevelMeterSource* source, int selectedChannel) override
{
    if (source == nullptr) { return; }

    juce::Rectangle<float> meter = getMeterBarBounds(bounds, meterType);
    if (!meter.isEmpty())
    {
        if ((meterType & foleys::LevelMeter::Reduction) != 0)
        {
            drawMeterBar(g, meterType, meter, source->getReductionLevel(selectedChannel), 0.0f);
        }
        else
        {
            drawMeterBar(g, meterType, meter, source->getRMSLevel(selectedChannel),
                         source->getMaxLevel(selectedChannel));
            const float reduction = source->getReductionLevel(selectedChannel);
            if (reduction < 1.0)
            {
                if ((meterType & foleys::LevelMeter::Horizontal) != 0)
                {
                    drawMeterReduction(g, meterType, meter.withBottom(meter.getCentreY()), reduction);
                }
                else
                {
                    drawMeterReduction(g, meterType, meter.withLeft(meter.getCentreX()), reduction);
                }
            }
        }
    }

    if (source->getClipFlag(selectedChannel))
    {
        juce::Rectangle<float> clip = getMeterClipIndicatorBounds(bounds, meterType);
        if (!clip.isEmpty()) { drawClipIndicator(g, meterType, clip, true); }
    }

    juce::Rectangle<float> maxes = getMeterMaxNumberBounds(bounds, meterType);
    if (!maxes.isEmpty())
    {
        if ((meterType & foleys::LevelMeter::Reduction) != 0)
        {
            drawMaxNumber(g, meterType, maxes, source->getReductionLevel(selectedChannel));
        }
        else
        {
            drawMaxNumber(g, meterType, maxes, source->getMaxOverallLevel(selectedChannel));
        }
    }
}

void drawMeterChannelBackground(juce::Graphics& g, foleys::LevelMeter::MeterFlags meterType,
                                juce::Rectangle<float> bounds) override
{
    juce::Rectangle<float> meter = getMeterBarBounds(bounds, meterType);
    if (!meter.isEmpty()) { drawMeterBarBackground(g, meterType, meter); }

    juce::Rectangle<float> clip = getMeterClipIndicatorBounds(bounds, meterType);
    if (!clip.isEmpty()) { drawClipIndicatorBackground(g, meterType, clip); }

    juce::Rectangle<float> ticks = getMeterTickmarksBounds(bounds, meterType);
    if (!ticks.isEmpty()) { drawTickMarks(g, meterType, ticks); }

    juce::Rectangle<float> maxes = getMeterMaxNumberBounds(bounds, meterType);
    if (!maxes.isEmpty()) { drawMaxNumberBackground(g, meterType, maxes); }
}

void drawMeterBar(juce::Graphics& g, foleys::LevelMeter::MeterFlags meterType, juce::Rectangle<float> bounds, float rms,
                  float peak) override
{
    const auto infinity = (meterType & foleys::LevelMeter::Reduction) != 0 ? -30.0f : -100.0f;
    const auto rmsDb    = juce::Decibels::gainToDecibels(rms, infinity);
    const auto peakDb   = juce::Decibels::gainToDecibels(peak, infinity);

    const juce::Rectangle<float> floored(ceilf(bounds.getX()) + 1.0f, ceilf(bounds.getY()) + 1.0f,
                                         floorf(bounds.getRight()) - (ceilf(bounds.getX() + 2.0f)),
                                         floorf(bounds.getBottom()) - (ceilf(bounds.getY()) + 2.0f));

    if ((meterType & foleys::LevelMeter::Vintage) != 0)
    {
        // TODO
    }
    else if ((meterType & foleys::LevelMeter::Reduction) != 0)
    {
        const float limitDb = juce::Decibels::gainToDecibels(rms, infinity);
        g.setColour(findColour(foleys::LevelMeter::lmMeterReductionColour));
        if ((meterType & foleys::LevelMeter::Horizontal) != 0)
        {
            g.fillRect(floored.withLeft(floored.getX() + limitDb * floored.getWidth() / infinity));
        }
        else
        {
            g.fillRect(floored.withBottom(floored.getY() + limitDb * floored.getHeight() / infinity));
        }
    }
    else
    {
        if ((meterType & foleys::LevelMeter::Horizontal) != 0)
        {
            if (horizontalGradient_.getNumColours() < 2)
            {
                horizontalGradient_
                    = juce::ColourGradient(findColour(foleys::LevelMeter::lmMeterGradientLowColour), floored.getX(),
                                           floored.getY(), findColour(foleys::LevelMeter::lmMeterGradientMaxColour),
                                           floored.getRight(), floored.getY(), false);
                horizontalGradient_.addColour(0.5, findColour(foleys::LevelMeter::lmMeterGradientLowColour));
                horizontalGradient_.addColour(0.75, findColour(foleys::LevelMeter::lmMeterGradientMidColour));
            }
            g.setGradientFill(horizontalGradient_);
            g.fillRect(floored.withRight(floored.getRight() - rmsDb * floored.getWidth() / infinity));

            if (peakDb > -49.0)
            {
                g.setColour(findColour((peakDb > -0.3f)
                                           ? foleys::LevelMeter::lmMeterMaxOverColour
                                           : ((peakDb > -5.0) ? foleys::LevelMeter::lmMeterMaxWarnColour
                                                              : foleys::LevelMeter::lmMeterMaxNormalColour)));
                g.drawVerticalLine(
                    juce::roundToInt(floored.getRight() - juce::jmax(peakDb * floored.getWidth() / infinity, 0.0f)),
                    floored.getY(), floored.getBottom());
            }
        }
        else
        {
            // vertical
            if (verticalGradient_.getNumColours() < 2)
            {
                verticalGradient_ = juce::ColourGradient(
                    findColour(foleys::LevelMeter::lmMeterGradientLowColour), floored.getX(), floored.getBottom(),
                    findColour(foleys::LevelMeter::lmMeterGradientMaxColour), floored.getX(), floored.getY(), false);
                verticalGradient_.addColour(0.5f, findColour(foleys::LevelMeter::lmMeterGradientLowColour));
                verticalGradient_.addColour(0.75f, findColour(foleys::LevelMeter::lmMeterGradientMidColour));
            }
            g.setGradientFill(verticalGradient_);
            g.fillRect(floored.withTop(floored.getY() + rmsDb * floored.getHeight() / infinity));

            if (peakDb > -49.0f)
            {
                g.setColour(findColour((peakDb > -0.3f)
                                           ? foleys::LevelMeter::lmMeterMaxOverColour
                                           : ((peakDb > -5.0f) ? foleys::LevelMeter::lmMeterMaxWarnColour
                                                               : foleys::LevelMeter::lmMeterMaxNormalColour)));
                g.drawHorizontalLine(
                    juce::roundToInt(floored.getY() + juce::jmax(peakDb * floored.getHeight() / infinity, 0.0f)),
                    floored.getX(), floored.getRight());
            }
        }
    }
}

void drawMeterReduction(juce::Graphics& g, foleys::LevelMeter::MeterFlags meterType, juce::Rectangle<float> bounds,
                        float reduction) override
{
    const auto infinity = -30.0f;

    const juce::Rectangle<float> floored(ceilf(bounds.getX()) + 1.0f, ceilf(bounds.getY()) + 1.0f,
                                         floorf(bounds.getRight()) - (ceilf(bounds.getX() + 2.0f)),
                                         floorf(bounds.getBottom()) - (ceilf(bounds.getY()) + 2.0f));

    const auto limitDb = juce::Decibels::gainToDecibels(reduction, infinity);
    g.setColour(findColour(foleys::LevelMeter::lmMeterReductionColour));
    if ((meterType & foleys::LevelMeter::Horizontal) != 0)
    {
        g.fillRect(floored.withLeft(floored.getX() + limitDb * floored.getWidth() / infinity));
    }
    else
    {
        g.fillRect(floored.withBottom(floored.getY() + limitDb * floored.getHeight() / infinity));
    }
}

void drawMeterBarBackground(juce::Graphics& g, foleys::LevelMeter::MeterFlags meterType,
                            juce::Rectangle<float> bounds) override
{
    juce::ignoreUnused(meterType);
    g.setColour(findColour(foleys::LevelMeter::lmMeterBackgroundColour));
    g.fillRect(bounds);

    g.setColour(findColour(foleys::LevelMeter::lmMeterOutlineColour));
    g.drawRect(bounds, 1.0);
}

void drawTickMarks(juce::Graphics& g, foleys::LevelMeter::MeterFlags meterType, juce::Rectangle<float> bounds) override
{
    const auto infinity = (meterType & foleys::LevelMeter::Reduction) != 0 ? -30.0f : -100.0f;

    g.setColour(findColour(foleys::LevelMeter::lmTicksColour));
    if ((meterType & foleys::LevelMeter::Minimal) != 0)
    {
        if ((meterType & foleys::LevelMeter::Horizontal) != 0)
        {
            for (int i = 0; i < 11; ++i)
            {
                g.drawVerticalLine(juce::roundToInt(bounds.getX() + i * 0.1f * bounds.getWidth()), bounds.getY() + 4,
                                   bounds.getBottom() - 4);
            }
        }
        else
        {
            const auto h = (bounds.getHeight() - 2.0f) * 0.1f;
            for (int i = 0; i < 11; ++i)
            {
                g.drawHorizontalLine(juce::roundToInt(bounds.getY() + i * h + 1), bounds.getX() + 4, bounds.getRight());
            }
            if (h > 10 && bounds.getWidth() > 20)
            {
                // don't print tiny numbers
                g.setFont(h * 0.5f);
                for (int i = 0; i < 10; ++i)
                {
                    g.drawFittedText(juce::String(i * 0.1 * infinity), juce::roundToInt(bounds.getX()),
                                     juce::roundToInt(bounds.getY() + i * h + 2), juce::roundToInt(bounds.getWidth()),
                                     juce::roundToInt(h * 0.6f), juce::Justification::centredTop, 1);
                }
            }
        }
    }
    else if ((meterType & foleys::LevelMeter::Vintage) != 0)
    {
        // TODO
    }
    else
    {
        if ((meterType & foleys::LevelMeter::Horizontal) != 0)
        {
            for (int i = 0; i < 11; ++i)
            {
                g.drawVerticalLine(juce::roundToInt(bounds.getX() + i * 0.1f * bounds.getWidth()), bounds.getY() + 4,
                                   bounds.getBottom() - 4);
            }
        }
        else
        {
            const auto h = (bounds.getHeight() - 2.0f) * 0.05f;
            g.setFont(h * 0.8f);
            for (int i = 0; i < 21; ++i)
            {
                const auto y = bounds.getY() + i * h;
                if (i % 2 == 0)
                {
                    g.drawHorizontalLine(juce::roundToInt(y + 1), bounds.getX() + 4, bounds.getRight());
                    if (i < 20)
                    {
                        g.drawFittedText(juce::String(i * 0.05 * infinity), juce::roundToInt(bounds.getX()),
                                         juce::roundToInt(y + 4), juce::roundToInt(bounds.getWidth()),
                                         juce::roundToInt(h * 0.6f), juce::Justification::topRight, 1);
                    }
                }
                else
                {
                    g.drawHorizontalLine(juce::roundToInt(y + 2), bounds.getX() + 4, bounds.getCentreX());
                }
            }
        }
    }
}

void drawClipIndicator(juce::Graphics& g, foleys::LevelMeter::MeterFlags meterType, juce::Rectangle<float> bounds,
                       bool hasClipped) override
{
    juce::ignoreUnused(meterType);

    g.setColour(findColour(hasClipped ? foleys::LevelMeter::lmBackgroundClipColour
                                      : foleys::LevelMeter::lmMeterBackgroundColour));
    g.fillRect(bounds);
    g.setColour(findColour(foleys::LevelMeter::lmMeterOutlineColour));
    g.drawRect(bounds, 1.0);
}

void drawClipIndicatorBackground(juce::Graphics& g, foleys::LevelMeter::MeterFlags meterType,
                                 juce::Rectangle<float> bounds) override
{
    juce::ignoreUnused(meterType);

    g.setColour(findColour(foleys::LevelMeter::lmMeterBackgroundColour));
    g.fillRect(bounds);
    g.setColour(findColour(foleys::LevelMeter::lmMeterOutlineColour));
    g.drawRect(bounds, 1.0);
}

void drawMaxNumber(juce::Graphics& g, foleys::LevelMeter::MeterFlags meterType, juce::Rectangle<float> bounds,
                   float maxGain) override
{
    juce::ignoreUnused(meterType);

    g.setColour(findColour(foleys::LevelMeter::lmMeterBackgroundColour));
    g.fillRect(bounds);
    const float maxDb = juce::Decibels::gainToDecibels(maxGain, -100.0f);
    g.setColour(findColour(maxDb > 0.0 ? foleys::LevelMeter::lmTextClipColour : foleys::LevelMeter::lmTextColour));
    g.setFont(bounds.getHeight() * 0.5f);
    g.drawFittedText(juce::String(maxDb, 1) + " dB", bounds.reduced(2.0).toNearestInt(), juce::Justification::centred,
                     1);
    g.setColour(findColour(foleys::LevelMeter::lmMeterOutlineColour));
    g.drawRect(bounds, 1.0);
}

void drawMaxNumberBackground(juce::Graphics& g, foleys::LevelMeter::MeterFlags meterType,
                             juce::Rectangle<float> bounds) override
{
    juce::ignoreUnused(meterType);

    g.setColour(findColour(foleys::LevelMeter::lmMeterBackgroundColour));
    g.fillRect(bounds);
}

auto hitTestClipIndicator(juce::Point<int> position, foleys::LevelMeter::MeterFlags meterType,
                          juce::Rectangle<float> bounds, const foleys::LevelMeterSource* source) const -> int override
{
    if (source != nullptr)
    {
        const int numChannels = source->getNumChannels();
        for (int i = 0; i < numChannels; ++i)
        {
            if (getMeterClipIndicatorBounds(getMeterBounds(bounds, meterType, source->getNumChannels(), i), meterType)
                    .contains(position.toFloat()))
            {
                return i;
            }
        }
    }
    return -1;
}

auto hitTestMaxNumber(juce::Point<int> position, foleys::LevelMeter::MeterFlags meterType,
                      juce::Rectangle<float> bounds, const foleys::LevelMeterSource* source) const -> int override
{
    if (source != nullptr)
    {
        const int numChannels = source->getNumChannels();
        for (int i = 0; i < numChannels; ++i)
        {
            if (getMeterMaxNumberBounds(getMeterBounds(bounds, meterType, source->getNumChannels(), i), meterType)
                    .contains(position.toFloat()))
            {
                return i;
            }
        }
    }
    return -1;
}

private:
juce::ColourGradient horizontalGradient_;
juce::ColourGradient verticalGradient_;
