namespace mc {

auto LottieShapeGradientStroke::parse(juce::var const& obj) -> LottieShapeGradientStroke
{
    auto const typeID = toString(obj["ty"]);
    if (typeID != LottieShapeGradientStroke::token) {
        raisef<InvalidArgument>("wrong ty for gradient-stroke shape: {}", typeID);
    }
    auto path = LottieShapeGradientStroke {};
    return path;
}

} // namespace mc
