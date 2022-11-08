#pragma once

namespace mc {

template <typename PropertyType>
auto LottieStaticProperty<PropertyType>::parse(juce::var const& obj) -> LottieStaticProperty<PropertyType>
{
    auto const animated = static_cast<int>(obj["a"]) == 1;
    if (animated) { raise<InvalidArgument>("animated, but parsing static"); }
    return { PropertyType::parse(obj["k"]) };
}

} // namespace mc