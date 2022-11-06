namespace mc {

auto LottieShapeFill::parse(juce::var const& obj) -> LottieShapeFill
{
    if (toString(obj["ty"]) != LottieShapeFill::token) { throw InvalidArgument { "wrong ty for fill shape" }; }
    auto fill = LottieShapeFill {};
    return fill;
}

} // namespace mc
