#ifndef MC_JUCE_BUNDLE_VALE_TREE_VARIANT_CONVERTER_HPP
#define MC_JUCE_BUNDLE_VALE_TREE_VARIANT_CONVERTER_HPP

template<>
struct juce::VariantConverter<juce::Colour>
{
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Colour { return Colour::fromString(v.toString()); }
    [[nodiscard]] static auto toVar(juce::Colour const& c) -> juce::var { return c.toString(); }
};

template<>
struct juce::VariantConverter<juce::Time>
{
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Time
    {
        return juce::Time::fromISO8601(v.toString());
    }

    [[nodiscard]] static auto toVar(juce::Time const& t) -> juce::var
    {
        auto str = t.toISO8601(true);
        return str;
    }
};

template<>
struct juce::VariantConverter<juce::Image>
{
    static auto fromVar(juce::var const& v) -> juce::Image
    {
        auto* mb = v.getBinaryData();
        if (mb == nullptr) { return {}; }
        return juce::ImageFileFormat::loadFrom(mb->getData(), mb->getSize());
    }

    static auto toVar(juce::Image const& i) -> juce::var
    {
        auto mb = juce::MemoryBlock {};
        auto os = juce::MemoryOutputStream(mb, false);
        if (!JPEGImageFormat().writeImageToStream(i, os)) { return {}; }
        return mb;
    }
};

template<typename ValueType>
struct juce::VariantConverter<juce::Range<ValueType>>
{
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Range<ValueType>
    {
        auto const splits = mc::StringUtils::split(v.toString(), ':');
        auto const start  = mc::StringUtils::toValue<ValueType>(splits[0]);
        auto const end    = mc::StringUtils::toValue<ValueType>(splits[1]);
        return juce::Range<ValueType> {start, end};
    }

    [[nodiscard]] static auto toVar(juce::Range<ValueType> const& r) -> juce::var
    {
        return juce::String {fmt::format("{}:{}", r.getStart(), r.getEnd())};
    }
};

template<typename ValueType>
struct juce::VariantConverter<juce::NormalisableRange<ValueType>>
{
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::NormalisableRange<ValueType>
    {
        auto const splits        = mc::StringUtils::split(v.toString(), ':');
        auto const start         = mc::StringUtils::toValue<ValueType>(splits[0]);
        auto const end           = mc::StringUtils::toValue<ValueType>(splits[1]);
        auto const interval      = mc::StringUtils::toValue<ValueType>(splits[2]);
        auto const skew          = mc::StringUtils::toValue<ValueType>(splits[3]);
        auto const symmetricSkew = static_cast<int>(mc::StringUtils::toValue<ValueType>(splits[4])) == 1;
        return juce::NormalisableRange<ValueType> {start, end, interval, skew, symmetricSkew};
    }

    [[nodiscard]] static auto toVar(juce::NormalisableRange<ValueType> const& nr) -> juce::var
    {
        return juce::String {fmt::format("{}:{}:{}:{}:{}", nr.start, nr.end, nr.interval, nr.skew, nr.symmetricSkew)};
    }
};

template<typename ValueType>
struct juce::VariantConverter<juce::Point<ValueType>>
{
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Point<ValueType>
    {
        auto const splits = mc::StringUtils::split(v.toString(), ':');
        auto const x      = mc::StringUtils::toValue<ValueType>(splits[0]);
        auto const y      = mc::StringUtils::toValue<ValueType>(splits[1]);
        return juce::Point<ValueType> {x, y};
    }

    [[nodiscard]] static auto toVar(juce::Point<ValueType> const& p) -> juce::var
    {
        return juce::String {fmt::format("{}:{}", p.x, p.y)};
    }
};

template<typename ValueType>
struct juce::VariantConverter<juce::Line<ValueType>>
{
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Line<ValueType>
    {
        auto const splits = mc::StringUtils::split(v.toString(), ':');
        auto const startX = mc::StringUtils::toValue<ValueType>(splits[0]);
        auto const startY = mc::StringUtils::toValue<ValueType>(splits[1]);
        auto const endX   = mc::StringUtils::toValue<ValueType>(splits[2]);
        auto const endY   = mc::StringUtils::toValue<ValueType>(splits[3]);
        return juce::Line<ValueType> {{startX, startY}, {endX, endY}};
    }

    [[nodiscard]] static auto toVar(juce::Line<ValueType> const& l) -> juce::var
    {
        return juce::String {fmt::format("{}:{}:{}:{}", l.getStart().x, l.getStart().y, l.getEnd().x, l.getEnd().y)};
    }
};

template<typename ValueType>
struct juce::VariantConverter<juce::Rectangle<ValueType>>
{
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Rectangle<ValueType>
    {
        auto const splits = mc::StringUtils::split(v.toString(), ':');
        auto const x      = mc::StringUtils::toValue<ValueType>(splits[0]);
        auto const y      = mc::StringUtils::toValue<ValueType>(splits[1]);
        auto const width  = mc::StringUtils::toValue<ValueType>(splits[2]);
        auto const height = mc::StringUtils::toValue<ValueType>(splits[3]);
        return juce::Rectangle<ValueType> {x, y, width, height};
    }

    [[nodiscard]] static auto toVar(juce::Rectangle<ValueType> const& l) -> juce::var
    {
        return juce::String {fmt::format("{}:{}:{}:{}", l.getX(), l.getY(), l.getWidth(), l.getHeight())};
    }
};

#endif  // MC_JUCE_BUNDLE_VALE_TREE_VARIANT_CONVERTER_HPP
