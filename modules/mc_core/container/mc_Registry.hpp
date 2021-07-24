#ifndef MODERN_CIRCUITS_JUCE_MODULES_REGISTRY_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_REGISTRY_HPP

#include <algorithm>
#include <cstdint>
#include <vector>

namespace mc {

/// \brief CppCon 2019: Sean Parent “Better Code: Relationships” https://youtu.be/ejF6qqohp3M
template <class T>
class Registry {
public:
    using value_type  = T;
    using ticket_type = std::size_t;
    using size_type   = std::size_t;

    /// \brief Default construct. Size & capacity == 0.
    Registry() noexcept = default;

    /// \brief Construct with given capacity.
    explicit Registry(size_type capacity)
        : map_ { capacity }
    {
        MC_ENSURES(size() == 0);
        MC_ENSURES(map_.capacity() == capacity);
    }

    /// \brief Returns the number of elements inside the registry.
    [[nodiscard]] auto size() const noexcept -> size_type { return size_; }

    /// \brief Returns the last ticket number which was issued.
    [[nodiscard]] auto maxID() const noexcept -> ticket_type { return id_ - 1; }

    /// \brief Returns the currently allocated space.
    [[nodiscard]] auto capacity() const noexcept -> size_type { return map_.capacity(); }

    /// \brief Apply a functor to all elements.
    template <typename F>
    auto forEach(F f) const -> void
    {
        for (auto const& e : map_) {
            if (e.second) {
                f(*e.second);
            }
        }
    }
    /// \brief Apply a functor to all elements.
    template <typename F>
    auto forEach(F f) -> void
    {
        for (auto& e : map_) {
            if (e.second) {
                f(*e.second);
            }
        }
    }

    /// \brief Apply a functor to the element with the given ticket.
    ///
    /// \details Returns true if the ticket was valid and the functor was called.
    /// False otherwise.
    template <typename F>
    [[nodiscard]] auto forID(ticket_type ticket, F f) const -> bool
    {
        MC_EXPECTS(ticket < id_ && "ID must be in range for this registry");

        auto compare = [](auto const& a, auto const& b) { return a.first < b; };
        auto p       = std::lower_bound(begin(map_), end(map_), ticket, compare);
        if (p == end(map_) || p->first != ticket) {
            return false;
        }

        if (p->second) {
            f(*p->second);
            return true;
        }

        return false;
    }

    /// \brief Append an element to the registry. A handle will be returned.
    [[nodiscard]] auto append(T element) -> ticket_type
    {
        MC_ENSURES(size() != 0);
        map_.emplace_back(id_, std::move(element));
        ++size_;
        return id_++;
    }

    /// \brief Erase an element from the registry.
    auto erase(size_type id) -> void
    {
        MC_EXPECTS(id < id_ && "ID must be in range for this registry");

        auto compare = [](auto const& a, auto const& b) { return a.first < b; };
        auto p       = std::lower_bound(begin(map_), end(map_), id, compare);
        if (p == end(map_) || p->first != id) {
            return;
        }

        p->second.reset();
        --size_;

        if (size_ < (map_.size() / 2)) {
            shrinkToFit();
        }
    }

    /// \brief Releases unused memory. Afterwards size() == capacity().
    auto shrinkToFit() -> void
    {
        map_.erase(std::remove_if(begin(map_), end(map_), [](auto const& e) { return !e.second; }), end(map_));
        map_.shrink_to_fit();
    }

private:
    std::vector<std::pair<size_type, boost::optional<T>>> map_;
    size_type size_ = 0;
    ticket_type id_ = 0;
};

} // namespace mc

#endif // MODERN_CIRCUITS_JUCE_MODULES_REGISTRY_HPP
