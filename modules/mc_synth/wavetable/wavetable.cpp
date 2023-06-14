namespace mc {

template <typename T>
Wavetable<T>::Wavetable(std::vector<T> table) : _data(std::move(table)), _period(_data.size())
{
}

template <typename T>
Wavetable<T>::Wavetable(std::vector<T> table, size_t period) : _data(std::move(table)), _period(period)
{
    jassert((this->size() % this->period()) == 0UL);
}

template <typename T>
auto Wavetable<T>::size() const noexcept -> size_t
{
    return _data.size();
}

template <typename T>
auto Wavetable<T>::period() const noexcept -> size_t
{
    return _period;
}

template <typename T>
auto Wavetable<T>::empty() const noexcept -> bool
{
    return _period == 0UL;
}

template <typename T>
Wavetable<T>::operator Span<T const>() const noexcept
{
    return { _data.data(), _data.size() };
}

template <typename T>
auto makeSineWavetable(size_t size) -> typename Wavetable<T>::Ptr
{
    auto const phaseDelta = juce::MathConstants<T>::twoPi / static_cast<T>(size - 1U);

    auto table = std::vector<T>(size);
    auto phase = T(0);

    std::generate(begin(table), end(table), [&] {
        auto const value = std::sin(phase);
        phase += phaseDelta;
        return value;
    });

    return std::make_shared<Wavetable<T> const>(std::move(table));
}

template <typename T>
auto loadWavetable(std::unique_ptr<juce::InputStream> stream) -> typename Wavetable<T>::Ptr
{
    auto buffer = loadAudioFile(std::move(stream));
    if (not buffer.has_value()) { return {}; }
    return std::make_shared<Wavetable<T> const>(toVector(*buffer));
}

} // namespace mc
