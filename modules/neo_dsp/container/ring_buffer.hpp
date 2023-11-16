#pragma once

namespace neo {

template <typename T>
struct RingBuffer {
    using value_type = T;
    using size_type  = std::size_t;

    RingBuffer();
    explicit RingBuffer(size_type size);

    [[nodiscard]] auto empty() const noexcept -> bool;
    [[nodiscard]] auto size() const noexcept -> size_type;

    auto clear() -> void;
    auto resize(size_type size) -> void;

    auto push(T value) -> void;
    [[nodiscard]] auto operator[](size_type index) const noexcept -> float;

private:
    std::vector<T> _buffer {};
    size_type _writePosition { 0 };
};

template <typename T>
RingBuffer<T>::RingBuffer() : RingBuffer { 1 }
{
}

template <typename T>
RingBuffer<T>::RingBuffer(size_type size)
{
    resize(size);
}

template <typename T>
auto RingBuffer<T>::operator[](size_type index) const noexcept -> float
{
    auto const i = _writePosition + index;
    if (i < _buffer.size()) { return _buffer[i]; }
    return _buffer[i - _buffer.size()];
}

template <typename T>
auto RingBuffer<T>::clear() -> void
{
    std::ranges::fill(_buffer, T {});
}

template <typename T>
auto RingBuffer<T>::resize(size_type size) -> void
{
    _buffer = std::vector<T>(size);
    clear();
}

template <typename T>
auto RingBuffer<T>::size() const noexcept -> size_type
{
    return _buffer.size();
}

template <typename T>
auto RingBuffer<T>::empty() const noexcept -> bool
{
    return size() == 0U;
}

template <typename T>
auto RingBuffer<T>::push(T value) -> void
{
    _buffer[_writePosition++] = value;
    if (_writePosition == _buffer.size()) { _writePosition = 0; }
}
} // namespace neo
