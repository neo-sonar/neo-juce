#pragma once

namespace mc {

template <typename T>
struct RingBuffer {
    using value_type = T;
    using size_type  = std::uint32_t;

    RingBuffer();
    explicit RingBuffer(size_type size);

    MC_NODISCARD auto empty() const noexcept -> bool;
    MC_NODISCARD auto size() const noexcept -> size_type;

    auto clear() -> void;
    auto resize(size_type size) -> void;

    auto push(T value) -> void;
    MC_NODISCARD auto operator[](size_type index) const noexcept -> float;

private:
    std::unique_ptr<T[]> buffer_ { nullptr }; // NOLINT(modernize-avoid-c-arrays)
    size_type size_ { 0 };
    size_type writePosition_ { 0 };
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
    auto const i = writePosition_ + index;
    if (i < size_) { return buffer_[i]; }
    return buffer_[i - size_];
}

template <typename T>
auto RingBuffer<T>::clear() -> void
{
    std::fill(buffer_.get(), std::next(buffer_.get(), size_), T {});
}

template <typename T>
auto RingBuffer<T>::resize(size_type size) -> void
{
    size_   = size;
    buffer_ = std::make_unique<T[]>(size); // NOLINT(modernize-avoid-c-arrays)
    clear();
}

template <typename T>
auto RingBuffer<T>::size() const noexcept -> size_type
{
    return size_;
}

template <typename T>
auto RingBuffer<T>::empty() const noexcept -> bool
{
    return size() == 0;
}

template <typename T>
auto RingBuffer<T>::push(T value) -> void
{
    buffer_[writePosition_++] = value;
    if (writePosition_ == size_) { writePosition_ = 0; }
}
} // namespace mc
