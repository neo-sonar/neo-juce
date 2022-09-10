#pragma once

namespace mc {
struct AirWindowsVerbity {
    struct Parameter {
        float big { 0.25f };
        float tail { 0.0f };
        float dark { 0.25f };
        float wet { 0.25f };
    };

    auto prepare(juce::dsp::ProcessSpec const& spec) -> void
    {
        spec_ = spec;
        reset();
    }

    auto process(juce::AudioBuffer<float>& buffer) -> void
    {
        std::uint32_t nSampleFrames = buffer.getNumSamples();
        auto const* source          = buffer.getReadPointer(0);
        auto* destination           = buffer.getWritePointer(0);

        long double overallscale = 1.0;
        overallscale /= 44100.0;
        overallscale *= spec_.sampleRate;
        int cycleEnd = floor(overallscale);
        if (cycleEnd < 1) cycleEnd = 1;
        if (cycleEnd > 4) cycleEnd = 4;
        // this is going to be 2 for 88.1 or 96k, 3 for silly people, 4 for 176 or 192k
        if (cycle > cycleEnd - 1) cycle = cycleEnd - 1; // sanity check

        double size          = (parameter_.big * 1.77) + 0.1;
        double regen         = 0.0625 + (parameter_.tail * 0.03125); // 0.09375 max;
        double lowpass       = (1.0 - pow(parameter_.dark, 2.0)) / sqrt(overallscale);
        double interpolate   = pow(parameter_.dark, 2.0) * 0.618033988749894848204586; // has IIRlike qualities
        double thunderAmount = (0.3 - (parameter_.tail * 0.22)) * parameter_.dark * 0.1;
        double wet           = parameter_.wet * 2.0;
        double dry           = 2.0 - wet;
        if (wet > 1.0) { wet = 1.0; }
        if (wet < 0.0) { wet = 0.0; }
        if (dry > 1.0) { dry = 1.0; }
        if (dry < 0.0) { dry = 0.0; }
        // this reverb makes 50% full dry AND full wet, not crossfaded.
        // that's so it can be on submixes without cutting back dry channel when adjusted:
        // unless you go super heavy, you are only adjusting the added verb loudness.

        delayI = 3407.0 * size;
        delayJ = 1823.0 * size;
        delayK = 859.0 * size;
        delayL = 331.0 * size;

        delayA = 4801.0 * size;
        delayB = 2909.0 * size;
        delayC = 1153.0 * size;
        delayD = 461.0 * size;

        delayE = 7607.0 * size;
        delayF = 4217.0 * size;
        delayG = 2269.0 * size;
        delayH = 1597.0 * size;

        while (nSampleFrames-- > 0) {
            long double inputSample = *source;
            if (fabs(inputSample) < 1.18e-37) inputSample = fpd * 1.18e-37;
            double drySample = inputSample;

            if (fabs(iirA) < 1.18e-37) iirA = 0.0;
            iirA        = (iirA * (1.0 - lowpass)) + (inputSample * lowpass);
            inputSample = iirA;
            // initial filter

            cycle++;
            if (cycle == cycleEnd) { // hit the end point and we do a reverb sample
                feedbackA = (feedbackA * (1.0 - interpolate)) + (previousA * interpolate);
                previousA = feedbackA;
                feedbackB = (feedbackB * (1.0 - interpolate)) + (previousB * interpolate);
                previousB = feedbackB;
                feedbackC = (feedbackC * (1.0 - interpolate)) + (previousC * interpolate);
                previousC = feedbackC;
                feedbackD = (feedbackD * (1.0 - interpolate)) + (previousD * interpolate);
                previousD = feedbackD;

                thunder = (thunder * 0.99) - (feedbackA * thunderAmount);

                aI[countI] = inputSample + ((feedbackA + thunder) * regen);
                aJ[countJ] = inputSample + (feedbackB * regen);
                aK[countK] = inputSample + (feedbackC * regen);
                aL[countL] = inputSample + (feedbackD * regen);

                countI++;
                if (countI < 0 || countI > delayI) countI = 0;
                countJ++;
                if (countJ < 0 || countJ > delayJ) countJ = 0;
                countK++;
                if (countK < 0 || countK > delayK) countK = 0;
                countL++;
                if (countL < 0 || countL > delayL) countL = 0;

                double outI = aI[countI - ((countI > delayI) ? delayI + 1 : 0)];
                double outJ = aJ[countJ - ((countJ > delayJ) ? delayJ + 1 : 0)];
                double outK = aK[countK - ((countK > delayK) ? delayK + 1 : 0)];
                double outL = aL[countL - ((countL > delayL) ? delayL + 1 : 0)];
                // first block: now we have four outputs

                aA[countA] = (outI - (outJ + outK + outL));
                aB[countB] = (outJ - (outI + outK + outL));
                aC[countC] = (outK - (outI + outJ + outL));
                aD[countD] = (outL - (outI + outJ + outK));

                countA++;
                if (countA < 0 || countA > delayA) countA = 0;
                countB++;
                if (countB < 0 || countB > delayB) countB = 0;
                countC++;
                if (countC < 0 || countC > delayC) countC = 0;
                countD++;
                if (countD < 0 || countD > delayD) countD = 0;

                double outA = aA[countA - ((countA > delayA) ? delayA + 1 : 0)];
                double outB = aB[countB - ((countB > delayB) ? delayB + 1 : 0)];
                double outC = aC[countC - ((countC > delayC) ? delayC + 1 : 0)];
                double outD = aD[countD - ((countD > delayD) ? delayD + 1 : 0)];
                // second block: four more outputs

                aE[countE] = (outA - (outB + outC + outD));
                aF[countF] = (outB - (outA + outC + outD));
                aG[countG] = (outC - (outA + outB + outD));
                aH[countH] = (outD - (outA + outB + outC));

                countE++;
                if (countE < 0 || countE > delayE) countE = 0;
                countF++;
                if (countF < 0 || countF > delayF) countF = 0;
                countG++;
                if (countG < 0 || countG > delayG) countG = 0;
                countH++;
                if (countH < 0 || countH > delayH) countH = 0;

                double outE = aE[countE - ((countE > delayE) ? delayE + 1 : 0)];
                double outF = aF[countF - ((countF > delayF) ? delayF + 1 : 0)];
                double outG = aG[countG - ((countG > delayG) ? delayG + 1 : 0)];
                double outH = aH[countH - ((countH > delayH) ? delayH + 1 : 0)];
                // third block: final outputs

                feedbackA = (outE - (outF + outG + outH));
                feedbackB = (outF - (outE + outG + outH));
                feedbackC = (outG - (outE + outF + outH));
                feedbackD = (outH - (outE + outF + outG));
                // which we need to feed back into the input again, a bit

                inputSample = (outE + outF + outG + outH) / 8.0;
                // and take the final combined sum of outputs
                if (cycleEnd == 4) {
                    lastRef[0] = lastRef[4];                     // start from previous last
                    lastRef[2] = (lastRef[0] + inputSample) / 2; // half
                    lastRef[1] = (lastRef[0] + lastRef[2]) / 2;  // one quarter
                    lastRef[3] = (lastRef[2] + inputSample) / 2; // three quarters
                    lastRef[4] = inputSample;                    // full
                }
                if (cycleEnd == 3) {
                    lastRef[0] = lastRef[3];                                   // start from previous last
                    lastRef[2] = (lastRef[0] + lastRef[0] + inputSample) / 3;  // third
                    lastRef[1] = (lastRef[0] + inputSample + inputSample) / 3; // two thirds
                    lastRef[3] = inputSample;                                  // full
                }
                if (cycleEnd == 2) {
                    lastRef[0] = lastRef[2];                     // start from previous last
                    lastRef[1] = (lastRef[0] + inputSample) / 2; // half
                    lastRef[2] = inputSample;                    // full
                }
                cycle = 0; // reset
            } else {
                inputSample = lastRef[cycle];
                // we are going through our references now
            }

            if (fabs(iirB) < 1.18e-37) iirB = 0.0;
            iirB        = (iirB * (1.0 - lowpass)) + (inputSample * lowpass);
            inputSample = iirB;
            // end filter

            if (wet < 1.0) inputSample *= wet;
            if (dry < 1.0) drySample *= dry;
            inputSample += drySample;
            // this is our submix verb dry/wet: 0.5 is BOTH at FULL VOLUME
            // purpose is that, if you're adding verb, you're not altering other balances

            // begin 32 bit floating point dither
            int expon;
            frexpf((float)inputSample, &expon);
            fpd ^= fpd << 13;
            fpd ^= fpd >> 17;
            fpd ^= fpd << 5;
            inputSample += ((double(fpd) - uint32_t(0x7fffffff)) * 5.5e-36l * pow(2, expon + 62));
            // end 32 bit floating point dither

            *destination = inputSample;

            source += inNumChannels;
            destination += inNumChannels;
        }
    }

    auto reset() -> void
    {
        iirA = 0.0;
        iirB = 0.0;

        for (int count = 0; count < 6479; count++) { aI[count] = 0.0; }
        for (int count = 0; count < 3659; count++) { aJ[count] = 0.0; }
        for (int count = 0; count < 1719; count++) { aK[count] = 0.0; }
        for (int count = 0; count < 679; count++) { aL[count] = 0.0; }

        for (int count = 0; count < 9699; count++) { aA[count] = 0.0; }
        for (int count = 0; count < 5999; count++) { aB[count] = 0.0; }
        for (int count = 0; count < 2319; count++) { aC[count] = 0.0; }
        for (int count = 0; count < 939; count++) { aD[count] = 0.0; }

        for (int count = 0; count < 15219; count++) { aE[count] = 0.0; }
        for (int count = 0; count < 8459; count++) { aF[count] = 0.0; }
        for (int count = 0; count < 4539; count++) { aG[count] = 0.0; }
        for (int count = 0; count < 3199; count++) { aH[count] = 0.0; }

        feedbackA = 0.0;
        feedbackB = 0.0;
        feedbackC = 0.0;
        feedbackD = 0.0;
        previousA = 0.0;
        previousB = 0.0;
        previousC = 0.0;
        previousD = 0.0;

        for (int count = 0; count < 6; count++) { lastRef[count] = 0.0; }

        thunder = 0;

        countI = 1;
        countJ = 1;
        countK = 1;
        countL = 1;

        countA = 1;
        countB = 1;
        countC = 1;
        countD = 1;

        countE = 1;
        countF = 1;
        countG = 1;
        countH = 1;

        cycle = 0;

        fpd = 1.0;
        while (fpd < 16386) { fpd = rand() * UINT32_MAX; }
    }

private:
    juce::dsp::ProcessSpec spec_ {};
    Parameter parameter_ {};

    double iirA;
    double iirB;

    double aI[6480];
    double aJ[3660];
    double aK[1720];
    double aL[680];

    double aA[9700];
    double aB[6000];
    double aC[2320];
    double aD[940];

    double aE[15220];
    double aF[8460];
    double aG[4540];
    double aH[3200];

    double feedbackA;
    double feedbackB;
    double feedbackC;
    double feedbackD;
    double previousA;
    double previousB;
    double previousC;
    double previousD;

    double lastRef[7];
    double thunder;

    int countA, delayA;
    int countB, delayB;
    int countC, delayC;
    int countD, delayD;
    int countE, delayE;
    int countF, delayF;
    int countG, delayG;
    int countH, delayH;
    int countI, delayI;
    int countJ, delayJ;
    int countK, delayK;
    int countL, delayL;
    int cycle;

    uint32_t fpd;
};
} // namespace mc
