#pragma once

namespace neo {
template <typename ParamT, typename StringLike, typename... Args>
auto makeParameter(StringLike&& id, Args&&... args)
{
    return std::make_unique<ParamT>(juce::ParameterID { std::forward<StringLike>(id), 1 }, std::forward<Args>(args)...);
}

template <typename StringLike, typename... Args>
auto makeFloatParameter(StringLike&& id, Args&&... args)
{
    return makeParameter<juce::AudioParameterFloat>(std::forward<StringLike>(id), std::forward<Args>(args)...);
}

template <typename StringLike, typename... Args>
auto makeIntParameter(StringLike&& id, Args&&... args)
{
    return makeParameter<juce::AudioParameterInt>(std::forward<StringLike>(id), std::forward<Args>(args)...);
}

template <typename StringLike, typename... Args>
auto makeChoiceParameter(StringLike&& id, Args&&... args)
{
    return makeParameter<juce::AudioParameterChoice>(std::forward<StringLike>(id), std::forward<Args>(args)...);
}

template <typename StringLike, typename... Args>
auto makeBoolParameter(StringLike&& id, Args&&... args)
{
    return makeParameter<juce::AudioParameterBool>(std::forward<StringLike>(id), std::forward<Args>(args)...);
}

} // namespace neo
