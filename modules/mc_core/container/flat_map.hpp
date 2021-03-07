#ifndef MODERN_CIRCUITS_JUCE_MODULES_FLAT_MAP_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_FLAT_MAP_HPP

namespace mc
{

/**
 * @brief
 *
 * @tparam Key
 * @tparam T
 * @tparam Compare
 * @tparam Container
 */
template<typename Key, typename T, typename Compare = std::less<Key>,
         typename Container = std::vector<std::pair<Key, T>>>
class FlatMap
{
public:
    using key_type               = Key;
    using mapped_type            = T;
    using value_type             = std::pair<Key, T>;
    using container_type         = Container;
    using key_compare            = Compare;
    using reference              = value_type&;
    using const_reference        = value_type const&;
    using allocator_type         = typename container_type::allocator_type;
    using pointer                = typename std::allocator_traits<allocator_type>::pointer;
    using const_pointer          = typename std::allocator_traits<allocator_type>::pointer;
    using iterator               = typename container_type::iterator;
    using const_iterator         = typename container_type::const_iterator;
    using reverse_iterator       = typename container_type::reverse_iterator;
    using const_reverse_iterator = typename container_type::const_reverse_iterator;
    using difference_type        = typename container_type::difference_type;
    using size_type              = typename container_type::size_type;

    /**
     * @brief Construct an empty FlatMap.
     */
    FlatMap() = default;

    /**
     * @brief Returns an iterator to the first element of the underlying container.
     */
    [[nodiscard]] auto begin() noexcept -> iterator { return container_.begin(); }

    /**
     * @brief Returns an iterator to the first element of the underlying container.
     */
    [[nodiscard]] auto begin() const noexcept -> const_iterator { return container_.begin(); }

    /**
     * @brief Returns an iterator to the end of the underlying container.
     */
    [[nodiscard]] auto end() noexcept -> iterator { return container_.end(); }

    /**
     * @brief Returns an iterator to the end of the underlying container.
     */
    [[nodiscard]] auto end() const noexcept -> const_iterator { return container_.end(); }

    /**
     * @brief Returns an iterator to the reverse beginning of the underlying container.
     */
    [[nodiscard]] auto rbegin() noexcept -> reverse_iterator { return container_.rbegin(); }

    /**
     * @brief Returns an iterator to the reverse beginning of the underlying container.
     */
    [[nodiscard]] auto rbegin() const noexcept -> const_reverse_iterator { return container_.rbegin(); }

    /**
     * @brief Returns an iterator to the reverse end of the underlying container.
     */
    [[nodiscard]] auto rend() noexcept -> reverse_iterator { return container_.rend(); }

    /**
     * @brief Returns an iterator to the reverse end of the underlying container.
     */
    [[nodiscard]] auto rend() const noexcept -> const_reverse_iterator { return container_.rend(); }

    /**
     * @brief Returns an iterator to the first element of the underlying container.
     */
    [[nodiscard]] auto cbegin() const noexcept -> const_iterator { return container_.cbegin(); }

    /**
     * @brief Returns an iterator to the end of the underlying container.
     */
    [[nodiscard]] auto cend() const noexcept -> const_iterator { return container_.cend(); }

    /**
     * @brief Returns true if the underlying container is empty.
     */
    [[nodiscard]] auto empty() const noexcept -> bool { return container_.empty(); }

    [[nodiscard]] auto size() const noexcept -> size_type { return container_.size(); }
    [[nodiscard]] auto max_size() const noexcept -> size_type { return container_.max_size(); }

private:
    struct PairCompare
    {
        PairCompare() = default;
        PairCompare(key_compare const& kc) : keyCompare_(kc) { }
        auto operator()(value_type const& a, key_type const& b) const -> bool { return keyCompare_(a.first, b); }
        auto operator()(key_type const& a, value_type const& b) const -> bool { return keyCompare_(a, b.first); }

        key_compare keyCompare_;
    };

    PairCompare compare_ {};
    container_type container_ {};
};
}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_FLAT_MAP_HPP
