#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_AIRWINDOWSCOILS2_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_AIRWINDOWSCOILS2_HPP

namespace mc
{
struct AirWindowsCoils2
{
    struct Parameter
    {
        float saturation {0.0f};
        float cheapness {0.0f};
        float dryWet {1.0f};
    };

    auto prepare(juce::dsp::ProcessSpec const& spec) -> void
    {
        spec_ = spec;
        reset();
    }

    auto process(juce::AudioBuffer<float>& buffer) -> void
    {
        float const* in1 = buffer.getReadPointer(0);
        float const* in2 = buffer.getReadPointer(1);
        float* out1      = buffer.getWritePointer(0);
        float* out2      = buffer.getWritePointer(1);

        double overallscale = 1.0;
        overallscale /= 44100.0;
        overallscale *= spec_.sampleRate;

        double distScaling = pow(1.0 - parameter_.saturation, 2);
        if (distScaling < 0.0001) distScaling = 0.0001;
        biquadA[0]            = 600.0 / spec_.sampleRate;
        biquadA[1]            = 0.01 + (pow(parameter_.cheapness, 2) * 0.5);
        long double iirAmount = biquadA[1] / overallscale;
        double K              = tan(M_PI * biquadA[0]);
        double norm           = 1.0 / (1.0 + K / biquadA[1] + K * K);
        biquadA[2]            = K / biquadA[1] * norm;
        biquadA[4]            = -biquadA[2];
        biquadA[5]            = 2.0 * (K * K - 1.0) * norm;
        biquadA[6]            = (1.0 - K / biquadA[1] + K * K) * norm;
        biquadB[0]            = (21890.0 - (biquadA[1] * 890.0)) / spec_.sampleRate;
        biquadB[1]            = 0.89;
        K                     = tan(M_PI * biquadB[0]);
        norm                  = 1.0 / (1.0 + K / biquadB[1] + K * K);
        biquadB[2]            = K * K * norm;
        biquadB[3]            = 2.0 * biquadB[2];
        biquadB[4]            = biquadB[2];
        biquadB[5]            = 2.0 * (K * K - 1.0) * norm;
        biquadB[6]            = (1.0 - K / biquadB[1] + K * K) * norm;
        double wet            = parameter_.dryWet;

        auto sampleFrames = buffer.getNumSamples();
        while (--sampleFrames >= 0)
        {
            long double inputSampleL = *in1;
            long double inputSampleR = *in2;
            if (fabs(inputSampleL) < 1.18e-37) inputSampleL = fpdL * 1.18e-37;
            if (fabs(inputSampleR) < 1.18e-37) inputSampleR = fpdR * 1.18e-37;
            long double drySampleL = inputSampleL;
            long double drySampleR = inputSampleR;

            if (biquadA[0] < 0.49999)
            {
                long double tempSample = (inputSampleL * biquadA[2]) + biquadA[7];
                biquadA[7]             = -(tempSample * biquadA[5]) + biquadA[8];
                biquadA[8]             = (inputSampleL * biquadA[4]) - (tempSample * biquadA[6]);
                inputSampleL           = tempSample;
                tempSample             = (inputSampleR * biquadA[2]) + biquadA[9];
                biquadA[9]             = -(tempSample * biquadA[5]) + biquadA[10];
                biquadA[10]            = (inputSampleR * biquadA[4]) - (tempSample * biquadA[6]);
                inputSampleR           = tempSample;  // create bandpass of clean tone
            }
            long double diffSampleL = (drySampleL - inputSampleL) / distScaling;
            long double diffSampleR = (drySampleR - inputSampleR) / distScaling;  // mids notched out
            if (biquadB[0] < 0.49999)
            {
                long double tempSample = (diffSampleL * biquadB[2]) + biquadB[7];
                biquadB[7]             = (diffSampleL * biquadB[3]) - (tempSample * biquadB[5]) + biquadB[8];
                biquadB[8]             = (diffSampleL * biquadB[4]) - (tempSample * biquadB[6]);
                diffSampleL            = tempSample;
                tempSample             = (diffSampleR * biquadB[2]) + biquadB[9];
                biquadB[9]             = (diffSampleR * biquadB[3]) - (tempSample * biquadB[5]) + biquadB[10];
                biquadB[10]            = (diffSampleR * biquadB[4]) - (tempSample * biquadB[6]);
                diffSampleR            = tempSample;
            }
            hysteresisL = (hysteresisL * (1.0 - iirAmount)) + (diffSampleL * iirAmount);
            if (fabs(hysteresisL) < 1.18e-37)
                hysteresisL = 0.0;
            else
                diffSampleL -= hysteresisL;
            if (diffSampleL > 1.571)
                diffSampleL = 1.571;
            else if (diffSampleL < -1.571)
                diffSampleL = -1.571;
            if (hysteresisL > 1.571)
                hysteresisL = 1.571;
            else if (hysteresisL < -1.571)
                hysteresisL = -1.571;

            hysteresisR = (hysteresisR * (1.0 - iirAmount)) + (diffSampleR * iirAmount);
            if (fabs(hysteresisR) < 1.18e-37)
                hysteresisR = 0.0;
            else
                diffSampleR -= hysteresisR;
            if (diffSampleR > 1.571)
                diffSampleR = 1.571;
            else if (diffSampleR < -1.571)
                diffSampleR = -1.571;
            if (hysteresisR > 1.571)
                hysteresisR = 1.571;
            else if (hysteresisR < -1.571)
                hysteresisR = -1.571;
            inputSampleL += (sin(diffSampleL) - sin(hysteresisL)) * distScaling;
            inputSampleR += (sin(diffSampleR) - sin(hysteresisR)) * distScaling;  // apply transformer distortions

            if (wet != 1.0)
            {
                inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0 - wet));
                inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0 - wet));
            }

            // begin 32 bit stereo floating point dither
            int expon;
            frexpf((float)inputSampleL, &expon);
            fpdL ^= fpdL << 13;
            fpdL ^= fpdL >> 17;
            fpdL ^= fpdL << 5;
            inputSampleL += ((double(fpdL) - uint32_t(0x7fffffff)) * 5.5e-36l * pow(2, expon + 62));
            frexpf((float)inputSampleR, &expon);
            fpdR ^= fpdR << 13;
            fpdR ^= fpdR >> 17;
            fpdR ^= fpdR << 5;
            inputSampleR += ((double(fpdR) - uint32_t(0x7fffffff)) * 5.5e-36l * pow(2, expon + 62));
            // end 32 bit stereo floating point dither

            *out1 = inputSampleL;
            *out2 = inputSampleR;

            juce::ignoreUnused(*in1++);
            juce::ignoreUnused(*in2++);
            juce::ignoreUnused(*out1++);
            juce::ignoreUnused(*out2++);
        }
    }

    auto reset() -> void
    {

        for (int x = 0; x < 15; x++)
        {
            biquadA[x] = 0.0;
            biquadB[x] = 0.0;
        }
        hysteresisL = hysteresisR = 0.0;
        fpdL                      = 1.0;
        while (fpdL < 16386) fpdL = rand() * UINT32_MAX;
        fpdR = 1.0;
        while (fpdR < 16386) fpdR = rand() * UINT32_MAX;
    }

private:
    juce::dsp::ProcessSpec spec_ {};
    Parameter parameter_ {};

    long double biquadA[15];
    long double biquadB[15];
    long double hysteresisL;
    long double hysteresisR;
    uint32_t fpdL;
    uint32_t fpdR;
    // default stuff

    //    float A;
    //    float B;
    //    float C;
};
}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MC_AIRWINDOWSCOILS2_HPP
