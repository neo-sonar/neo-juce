namespace mc {

auto LottieShapeTrim::parse(juce::var const& obj) -> LottieShapeTrim
{
    auto const typeID = toString(obj["ty"]);
    if (typeID != LottieShapeTrim::token) { raisef<InvalidArgument>("wrong ty for trim shape: {}", typeID); }
    auto path = LottieShapeTrim {};
    return path;
}

} // namespace mc
