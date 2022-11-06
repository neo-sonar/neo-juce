namespace mc {

auto LottieShapeTransform::parse(juce::var const& obj) -> LottieShapeTransform
{
    if (toString(obj["ty"]) != LottieShapeTransform::token) {
        throw InvalidArgument { "wrong ty for transform shape" };
    }
    auto transform = LottieShapeTransform {};
    return transform;
}

} // namespace mc
