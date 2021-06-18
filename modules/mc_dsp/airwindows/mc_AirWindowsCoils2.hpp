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
        if (distScaling < 0.0001) { distScaling = 0.0001; }
        biquadA_[0]           = 600.0 / spec_.sampleRate;
        biquadA_[1]           = 0.01 + (pow(parameter_.cheapness, 2) * 0.5);
        long double iirAmount = biquadA_[1] / overallscale;
        double k              = tan(M_PI * biquadA_[0]);
        double norm           = 1.0 / (1.0 + k / biquadA_[1] + k * k);
        biquadA_[2]           = k / biquadA_[1] * norm;
        biquadA_[4]           = -biquadA_[2];
        biquadA_[5]           = 2.0 * (k * k - 1.0) * norm;
        biquadA_[6]           = (1.0 - k / biquadA_[1] + k * k) * norm;
        biquadB_[0]           = (21890.0 - (biquadA_[1] * 890.0)) / spec_.sampleRate;
        biquadB_[1]           = 0.89;
        k                     = tan(M_PI * biquadB_[0]);
        norm                  = 1.0 / (1.0 + k / biquadB_[1] + k * k);
        biquadB_[2]           = k * k * norm;
        biquadB_[3]           = 2.0 * biquadB_[2];
        biquadB_[4]           = biquadB_[2];
        biquadB_[5]           = 2.0 * (k * k - 1.0) * norm;
        biquadB_[6]           = (1.0 - k / biquadB_[1] + k * k) * norm;
        double wet            = parameter_.dryWet;

        auto sampleFrames = buffer.getNumSamples();
        while (--sampleFrames >= 0)
        {
            long double inputSampleL = *in1;
            long double inputSampleR = *in2;
            if (std::abs(inputSampleL) < 1.18e-37) { inputSampleL = fpdL_ * 1.18e-37; }
            if (std::abs(inputSampleR) < 1.18e-37) { inputSampleR = fpdR_ * 1.18e-37; }
            long double drySampleL = inputSampleL;
            long double drySampleR = inputSampleR;

            if (biquadA_[0] < 0.49999)
            {
                long double tempSample = (inputSampleL * biquadA_[2]) + biquadA_[7];
                biquadA_[7]            = -(tempSample * biquadA_[5]) + biquadA_[8];
                biquadA_[8]            = (inputSampleL * biquadA_[4]) - (tempSample * biquadA_[6]);
                inputSampleL           = tempSample;
                tempSample             = (inputSampleR * biquadA_[2]) + biquadA_[9];
                biquadA_[9]            = -(tempSample * biquadA_[5]) + biquadA_[10];
                biquadA_[10]           = (inputSampleR * biquadA_[4]) - (tempSample * biquadA_[6]);
                inputSampleR           = tempSample;  // create bandpass of clean tone
            }
            long double diffSampleL = (drySampleL - inputSampleL) / distScaling;
            long double diffSampleR = (drySampleR - inputSampleR) / distScaling;  // mids notched out
            if (biquadB_[0] < 0.49999)
            {
                long double tempSample = (diffSampleL * biquadB_[2]) + biquadB_[7];
                biquadB_[7]            = (diffSampleL * biquadB_[3]) - (tempSample * biquadB_[5]) + biquadB_[8];
                biquadB_[8]            = (diffSampleL * biquadB_[4]) - (tempSample * biquadB_[6]);
                diffSampleL            = tempSample;
                tempSample             = (diffSampleR * biquadB_[2]) + biquadB_[9];
                biquadB_[9]            = (diffSampleR * biquadB_[3]) - (tempSample * biquadB_[5]) + biquadB_[10];
                biquadB_[10]           = (diffSampleR * biquadB_[4]) - (tempSample * biquadB_[6]);
                diffSampleR            = tempSample;
            }
            hysteresisL_ = (hysteresisL_ * (1.0 - iirAmount)) + (diffSampleL * iirAmount);
            if (std::abs(hysteresisL_) < 1.18e-37) { hysteresisL_ = 0.0; }
            else
            {
                diffSampleL -= hysteresisL_;
            }
            if (diffSampleL > 1.571) { diffSampleL = 1.571; }
            else if (diffSampleL < -1.571)
            {
                diffSampleL = -1.571;
            }
            if (hysteresisL_ > 1.571) { hysteresisL_ = 1.571; }
            else if (hysteresisL_ < -1.571)
            {
                hysteresisL_ = -1.571;
            }

            hysteresisR_ = (hysteresisR_ * (1.0 - iirAmount)) + (diffSampleR * iirAmount);
            if (std::abs(hysteresisR_) < 1.18e-37) { hysteresisR_ = 0.0; }
            else
            {
                diffSampleR -= hysteresisR_;
            }
            if (diffSampleR > 1.571) { diffSampleR = 1.571; }
            else if (diffSampleR < -1.571)
            {
                diffSampleR = -1.571;
            }
            if (hysteresisR_ > 1.571) { hysteresisR_ = 1.571; }
            else if (hysteresisR_ < -1.571)
            {
                hysteresisR_ = -1.571;
            }
            inputSampleL += (sin(diffSampleL) - sin(hysteresisL_)) * distScaling;
            inputSampleR += (sin(diffSampleR) - sin(hysteresisR_)) * distScaling;  // apply transformer distortions

            if (wet != 1.0)
            {
                inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0 - wet));
                inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0 - wet));
            }

            // begin 32 bit stereo floating point dither
            int expon;
            frexpf((float)inputSampleL, &expon);
            fpdL_ ^= fpdL_ << 13;
            fpdL_ ^= fpdL_ >> 17;
            fpdL_ ^= fpdL_ << 5;
            inputSampleL += ((double(fpdL_) - uint32_t(0x7fffffff)) * 5.5e-36L * pow(2, expon + 62));
            frexpf((float)inputSampleR, &expon);
            fpdR_ ^= fpdR_ << 13;
            fpdR_ ^= fpdR_ >> 17;
            fpdR_ ^= fpdR_ << 5;
            inputSampleR += ((double(fpdR_) - uint32_t(0x7fffffff)) * 5.5e-36L * pow(2, expon + 62));
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
            biquadA_[x] = 0.0;
            biquadB_[x] = 0.0;
        }
        hysteresisL_ = hysteresisR_ = 0.0;
        fpdL_                       = 1.0;
        while (fpdL_ < 16386) { fpdL_ = rand() * UINT32_MAX; }
        fpdR_ = 1.0;
        while (fpdR_ < 16386) { fpdR_ = rand() * UINT32_MAX; }
    }

private:
    juce::dsp::ProcessSpec spec_ {};
    Parameter parameter_ {};

    long double biquadA_[15] {};
    long double biquadB_[15] {};
    long double hysteresisL_ {};
    long double hysteresisR_ {};
    uint32_t fpdL_ {};
    uint32_t fpdR_ {};
    // default stuff

    //    float A;
    //    float B;
    //    float C;
};
}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MC_AIRWINDOWSCOILS2_HPP
