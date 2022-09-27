#pragma once

namespace mc {

template <typename T>
struct Averager {
    using value_type = T;

    Averager() = default;
    Averager(size_t numWindows, size_t windowSize);

    auto resize(size_t numWindows, size_t windowSize) -> void;
    auto clear() -> void;

    auto push(Span<T const> buffer) -> void;
    [[nodiscard]] auto average() const -> Span<T const>;

private:
    Vector<Vector<T>> _history {};
    Vector<T> _average {};
    std::size_t _writeIndex { 0 };
};

template <typename T>
Averager<T>::Averager(size_t numWindows, size_t windowSize)
{
    resize(numWindows, windowSize);
}

template <typename T>
auto Averager<T>::resize(size_t numWindows, size_t windowSize) -> void
{
    _history.resize(numWindows);
    _average.resize(windowSize);
    for (auto& buf : _history) { buf.resize(windowSize); }
}

template <typename T>
auto Averager<T>::clear() -> void
{
    ranges::fill(_average, T {});
    for (auto& buf : _history) { ranges::fill(buf, T {}); }
}

template <typename T>
auto Averager<T>::push(Span<T const> buffer) -> void
{
    // Copy input
    auto& dest = _history[_writeIndex];
    ranges::copy(buffer, ranges::begin(dest));
    _writeIndex = (_writeIndex + 1) % _history.size();

    // Calculate average
    ranges::fill(_average, T {});
    for (auto const& buf : _history) { ranges::transform(_average, buf, ranges::begin(_average), std::plus {}); }
    auto const scale = [n = static_cast<T>(_history.size())](auto v) { return v / n; };
    ranges::transform(_average, ranges::begin(_average), scale);
}

template <typename T>
auto Averager<T>::average() const -> Span<T const>
{
    return _average;
}

} // namespace mc