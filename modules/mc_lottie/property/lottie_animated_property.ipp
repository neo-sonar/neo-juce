#pragma once

namespace mc {

template <typename PropertyType>
auto LottieAnimatedProperty<PropertyType>::parse(juce::var const& obj) -> LottieAnimatedProperty<PropertyType>
{
    auto const animated = static_cast<int>(obj["a"]) == 1;
    if (not animated) { raise<InvalidArgument>("static, but parsing animated"); }
    // PropertyType::parse(obj["k"])
    return {};
}

} // namespace mc
