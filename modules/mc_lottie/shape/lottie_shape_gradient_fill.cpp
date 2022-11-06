namespace mc {

auto LottieShapeGradientFill::parse(juce::var const& obj) -> LottieShapeGradientFill
{
    auto const typeID = toString(obj["ty"]);
    if (typeID != LottieShapeGradientFill::token) {
        raisef<InvalidArgument>("wrong ty for gradient-fill shape: {}", typeID);
    }
    auto path = LottieShapeGradientFill {};
    return path;
}

} // namespace mc
