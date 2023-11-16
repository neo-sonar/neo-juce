#pragma once

namespace neo::fx {

template <typename T>
inline auto AirWindowsDeRez<T>::parameter(Parameter const& param) -> void
{
    auto overallscale = T { 1 };
    overallscale /= T { 44100 };
    overallscale *= static_cast<T>(_spec.sampleRate);

    _targetA = std::pow(param.rate, T(3)) + T(0.0005);
    if (_targetA > T(1)) { _targetA = T(1); }
    _soften  = (T(1) + _targetA) / 2;
    _targetB = std::pow(T(1) - param.resolution, T(3)) / T(3);
    _targetA /= overallscale;
}

template <typename T>
inline auto AirWindowsDeRez<T>::prepare(juce::dsp::ProcessSpec const& spec) -> void
{
    _spec = spec;
}

template <typename T>
inline auto AirWindowsDeRez<T>::reset() noexcept -> void
{
}

template <typename T>
template <typename ProcessContext>
inline auto AirWindowsDeRez<T>::process(ProcessContext const& context) noexcept -> void
{
    auto const& inputBlock = context.getInputBlock();
    auto& outputBlock      = context.getOutputBlock();
    outputBlock.copyFrom(inputBlock);

    auto const* in1 = inputBlock.getChannelPointer(0);
    auto* out1      = outputBlock.getChannelPointer(0);

    auto sampleFrames = static_cast<int>(inputBlock.getNumSamples());
    while (--sampleFrames >= 0) {
        _incrementFrequency = ((_incrementFrequency * T(999)) + _targetA) / T(1000);
        _incrementBitDepth  = ((_incrementBitDepth * T(999)) + _targetB) / T(1000);
        _position += _incrementFrequency;

        auto inputSample = *in1;
        auto drySample   = inputSample;

        auto outputSample = _heldSample;
        if (_position > T(1)) {
            _position -= T(1);
            _heldSample  = (_lastSample * _position) + (inputSample * (T(1) - _position));
            outputSample = (outputSample * (T(1) - _soften)) + (_heldSample * _soften);
            // softens the edge of the derez
        }
        inputSample = outputSample;

        auto offset { T(0) };
        if (_incrementBitDepth > T(0.0005)) {
            if (inputSample > 0) {
                offset = inputSample;
                while (offset > 0) { offset -= _incrementBitDepth; }
                inputSample -= offset; // it's below 0 so subtracting adds the remainder
            }

            if (inputSample < 0) {
                offset = inputSample;
                while (offset < 0) { offset += _incrementBitDepth; }
                inputSample -= offset; // it's above 0 so subtracting subtracts the remainder
            }

            inputSample *= (T(1) - _incrementBitDepth);
        }

        _lastSample = drySample;
        *out1       = inputSample;

        ++in1;
        ++out1;
    }
}

} // namespace neo::fx
