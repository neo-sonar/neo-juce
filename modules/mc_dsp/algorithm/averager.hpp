#pragma once

namespace mc {

template <typename T>
struct Averager {
    using value_type = T;

    Averager() = default;
    Averager(size_t numWindows, size_t windowSize);

    auto resize(size_t numWindows, size_t windowSize) -> void;
    auto clear() -> void;

    auto push(std::span<T const> buffer) -> void;
    [[nodiscard]] auto average() const -> std::span<T const>;

private:
    std::vector<std::vector<T>> _history {};
    std::vector<T> _average {};
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
    std::ranges::fill(_average, T {});
    for (auto& buf : _history) { std::ranges::fill(buf, T {}); }
}

template <typename T>
auto Averager<T>::push(std::span<T const> buffer) -> void
{
    // Copy input
    auto& dest = _history[_writeIndex];
    std::ranges::copy(buffer, std::ranges::begin(dest));
    _writeIndex = (_writeIndex + 1) % _history.size();

    // Calculate average
    std::ranges::fill(_average, T {});
    for (auto const& buf : _history) {
        std::ranges::transform(_average, buf, std::ranges::begin(_average), std::plus {});
    }
    auto const scale = [n = static_cast<T>(_history.size())](auto v) { return v / n; };
    std::ranges::transform(_average, std::ranges::begin(_average), scale);
}

template <typename T>
auto Averager<T>::average() const -> std::span<T const>
{
    return _average;
}

} // namespace mc
