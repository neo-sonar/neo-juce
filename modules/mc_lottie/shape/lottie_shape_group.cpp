
namespace mc {

auto LottieShapeGroup::parse(LottieShape group, juce::var const& obj) -> LottieShape
{
    auto const* array = obj["it"].getArray();
    if (array == nullptr) { raise<InvalidArgument>("no shapes in group"); }

    auto children = Vector<LottieShape> {};
    for (auto const& shapeObj : *array) { children.push_back(LottieShape::parse(group.registry, shapeObj)); }
    group.registry.emplace<LottieShapeGroup>(group.id, std::move(children));

    return group;
}

} // namespace mc
