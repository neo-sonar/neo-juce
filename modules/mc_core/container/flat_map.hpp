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
     * @brief
     */
    explicit FlatMap(key_compare const& cmp, allocator_type const& alloc = allocator_type())
        : compare_(cmp), container_(alloc)
    {
    }

    /**
     * @brief Defaulted copy constructor
     */
    FlatMap(FlatMap const& other) = default;

    /**
     * @brief Defaulted move constructor
     */
    FlatMap(FlatMap&& other) = default;

    /**
     * @brief Copy assignment
     */
    FlatMap& operator=(FlatMap const& other)
    {
        compare_   = other.compare_;
        container_ = other.container_;
        return *this;
    }

    /**
     * @brief Move assignment
     */
    FlatMap& operator=(FlatMap&& other)
    {
        compare_   = std::move(other.compare_);
        container_ = std::move(other.container_);
        return *this;
    }

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

    auto reserve(size_type count) -> void { return container_.reserve(count); }

    [[nodiscard]] auto capacity() const noexcept -> size_type { return container_.capacity(); }

    auto clear() noexcept -> void { container_.clear(); }

    [[nodiscard]] auto lower_bound(key_type const& k) -> iterator
    {
        return std::lower_bound(container_.begin(), container_.end(), k, compare_);
    }

    [[nodiscard]] auto lower_bound(key_type const& k) const -> const_iterator
    {
        return std::lower_bound(container_.begin(), container_.end(), k, compare_);
    }

    [[nodiscard]] auto find(key_type const& k) -> iterator
    {
        auto i = lower_bound(k);
        if (i != end() && !compare_(k, *i)) return i;

        return end();
    }

    [[nodiscard]] auto find(key_type const& k) const -> const_iterator
    {
        auto i = lower_bound(k);
        if (i != end() && !compare_(k, *i)) return i;

        return end();
    }

    [[nodiscard]] auto count(key_type const& k) const -> size_type { return find(k) == end() ? 0 : 1; }

    template<typename P>
    [[nodiscard]] auto insert(P&& val) -> std::pair<iterator, bool>
    {
        auto i = lower_bound(val.first);
        if (i != end() && !compare_(val.first, *i)) { return {i, false}; }

        return {container_.emplace(i, std::forward<P>(val)), true};
    }

    [[nodiscard]] auto insert(value_type const& val) -> std::pair<iterator, bool>
    {
        auto i = lower_bound(val.first);
        if (i != end() && !compare_(val.first, *i)) { return {i, false}; }

        return {container_.emplace(i, val), true};
    }

    template<typename... Args>
    [[nodiscard]] auto emplace(Args&&... args) -> std::pair<iterator, bool>
    {
        value_type val(std::forward<Args>(args)...);
        return insert(std::move(val));
    }

    auto erase(const_iterator pos) -> iterator { return container_.erase(pos); }

    auto erase(key_type const& k) -> size_type
    {
        if (auto i = find(k); i != end())
        {
            erase(i);
            return 1;
        }
        return 0;
    }

    [[nodiscard]] auto operator[](key_type const& k) -> mapped_type&
    {
        auto i = lower_bound(k);
        if (i != end() && !compare_(k, *i)) { return i->second; }

        i = container_.emplace(i, k, mapped_type());
        return i->second;
    }

    [[nodiscard]] auto operator[](key_type&& k) -> mapped_type&
    {
        auto i = lower_bound(k);
        if (i != end() && !compare_(k, *i)) { return i->second; }

        i = container_.emplace(i, std::forward<key_type>(k), mapped_type());
        return i->second;
    }

    [[nodiscard]] auto at(key_type const& k) -> mapped_type&
    {
        auto i = lower_bound(k);
        if (i == end() || compare_(*i, k)) { throw std::out_of_range("mc::FlatMap out of range"); }

        return i->second;
    }

    [[nodiscard]] auto at(key_type const& k) const -> mapped_type const&
    {
        auto i = lower_bound(k);
        if (i == end() || compare_(*i, k)) { throw std::out_of_range("mc::FlatMap out of range"); }

        return i->second;
    }

    auto swap(FlatMap& x) -> void
    {
        std::swap(compare_, x.compare_);
        container_.swap(x.container_);
    }

    [[nodiscard]] auto container() const noexcept -> container_type const& { return container_; }

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

template<typename Key, typename T, typename Compare, typename Container>
[[nodiscard]] auto operator==(FlatMap<Key, T, Compare, Container> const& lhs,
                              FlatMap<Key, T, Compare, Container> const& rhs) -> bool
{
    return lhs.container() == rhs.container();
}

template<typename Key, typename T, typename Compare, typename Container>
[[nodiscard]] auto operator!=(FlatMap<Key, T, Compare, Container> const& lhs,
                              FlatMap<Key, T, Compare, Container> const& rhs) -> bool
{
    return lhs.container() != rhs.container();
}

}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_FLAT_MAP_HPP
