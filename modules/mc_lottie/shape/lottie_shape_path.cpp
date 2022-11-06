namespace mc {

auto LottieShapePath::parse(juce::var const& obj) -> LottieShapePath
{
    auto const typeID = toString(obj["ty"]);
    if (typeID != LottieShapePath::token) { raisef<InvalidArgument>("wrong ty for path shape: {}", typeID); }
    auto path = LottieShapePath {};
    return path;
}

} // namespace mc
