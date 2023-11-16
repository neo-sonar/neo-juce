// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace neo {

/// \brief CppCon 2019: Sean Parent “Better Code: Relationships” https://youtu.be/ejF6qqohp3M
template <typename T>
struct Registry {
    using value_type  = T;
    using ticket_type = std::size_t;
    using size_type   = std::size_t;

    /// \brief Default construct. Size & capacity == 0.
    Registry() noexcept = default;

    /// \brief Construct with given capacity.
    explicit Registry(size_type capacity);

    /// \brief Returns the number of elements inside the registry.
    [[nodiscard]] auto size() const noexcept -> size_type;

    /// \brief Returns the last ticket number which was issued.
    [[nodiscard]] auto maxID() const noexcept -> ticket_type;

    /// \brief Returns the currently allocated space.
    [[nodiscard]] auto capacity() const noexcept -> size_type;

    /// \brief Apply a functor to all elements.
    template <typename F>
    auto forEach(F f) const -> void;

    /// \brief Apply a functor to all elements.
    template <typename F>
    auto forEach(F f) -> void;

    /// \brief Apply a functor to the element with the given ticket.
    ///
    /// \details Returns true if the ticket was valid and the functor was called.
    /// False otherwise.
    template <typename F>
    [[nodiscard]] auto forID(ticket_type ticket, F f) const -> bool;

    /// \brief Append an element to the registry. A handle will be returned.
    [[nodiscard]] auto append(T element) -> ticket_type;

    /// \brief Erase an element from the registry.
    auto erase(size_type id) -> void;

    /// \brief Releases unused memory. Afterwards size() == capacity().
    auto shrinkToFit() -> void;

private:
    std::vector<std::pair<size_type, std::optional<T>>> _map;
    size_type _size = 0;
    ticket_type _id = 0;
};

template <typename T>
Registry<T>::Registry(size_type capacity) : _map { capacity }
{
}

template <typename T>
auto Registry<T>::size() const noexcept -> size_type
{
    return _size;
}

template <typename T>
auto Registry<T>::maxID() const noexcept -> ticket_type
{
    return _id - 1;
}

template <typename T>
auto Registry<T>::capacity() const noexcept -> size_type
{
    return _map.capacity();
}

template <typename T>
template <typename F>
auto Registry<T>::forEach(F f) const -> void
{
    for (auto const& e : _map) {
        if (e.second) { f(*e.second); }
    }
}

template <typename T>
template <typename F>
auto Registry<T>::forEach(F f) -> void
{
    for (auto& e : _map) {
        if (e.second) { f(*e.second); }
    }
}

template <typename T>
template <typename F>
auto Registry<T>::forID(ticket_type ticket, F f) const -> bool
{
    jassert(ticket < _id);

    auto compare = [](auto const& a, auto const& b) { return a.first < b; };
    auto p       = std::lower_bound(begin(_map), end(_map), ticket, compare);
    if (p == end(_map) || p->first != ticket) { return false; }

    if (p->second) {
        f(*p->second);
        return true;
    }

    return false;
}

template <typename T>
auto Registry<T>::append(T element) -> ticket_type
{
    _map.emplace_back(_id, std::move(element));
    ++_size;
    return _id++;
}

template <typename T>
auto Registry<T>::erase(size_type id) -> void
{
    jassert(id < _id);

    auto compare = [](auto const& a, auto const& b) { return a.first < b; };
    auto p       = std::lower_bound(begin(_map), end(_map), id, compare);
    if (p == end(_map) || p->first != id) { return; }

    p->second.reset();
    --_size;

    if (_size < (_map.size() / 2)) { shrinkToFit(); }
}

template <typename T>
auto Registry<T>::shrinkToFit() -> void
{
    _map.erase(std::remove_if(begin(_map), end(_map), [](auto const& e) { return !e.second; }), end(_map));
    _map.shrink_to_fit();
}

} // namespace neo
