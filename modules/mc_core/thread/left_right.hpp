#ifndef MODERN_CIRCUITS_JUCE_MODULES_LEFT_RIGHT_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_LEFT_RIGHT_HPP

namespace mc
{
struct InPlaceTag
{
};

inline constexpr InPlaceTag InPlace {};

/**
 * Wrap any single-threaded data-structure with Left-Right
 * concurrency control
 *
 * Left-Right concurrency allows wait-free population-oblivious reads
 * and blocking writes. Writers never block readers.
 *
 * Instances of this class maintain two full copies of the underlying
 * data-structure and all modifications are performed twice. Consequently,
 * uses of this class should be limited to small amounts of data where
 * the number of reads dominates the number of writes.
 */
template<typename T, typename ReaderRegistry>
class BasicLeftRight  // NOLINT(clang-analyzer-optin.performance.Padding)
{
    static_assert(noexcept(std::declval<ReaderRegistry>().arrive()), "ReaderRegistry::arrive() must be noexcept");
    static_assert(noexcept(std::declval<ReaderRegistry>().depart()), "ReaderRegistry::depart() must be noexcept");
    static_assert(noexcept(std::declval<const ReaderRegistry>().empty()), "ReaderRegistry::empty() must be noexcept");

public:
    using value_type      = T;
    using reference       = value_type&;
    using const_reference = value_type const&;

    /**
     * Default construct left & right values.
     */
    BasicLeftRight() = default;

    /**
     * Construct the two underlying instances of T by moving a seed instance
     */
    explicit BasicLeftRight(value_type&& seed) noexcept(
        std::is_nothrow_copy_constructible_v<value_type>&& std::is_nothrow_move_constructible_v<value_type>)
        : leftValue_ {std::move(seed)}, rightValue_ {leftValue_}
    {
    }

    /**
     * Construct the two underlying instances of T by copying a seed instance
     */
    explicit BasicLeftRight(value_type const& seed) noexcept(std::is_nothrow_copy_constructible_v<value_type>)
        : leftValue_ {seed}, rightValue_ {seed}
    {
    }

    /**
     * Construct the two underlying instances of T in place, forwarding the args after the InPlace tag.
     */
    template<typename... Args>
    explicit BasicLeftRight(InPlaceTag tag, Args&&... args) noexcept(
        std::is_nothrow_copy_constructible_v<T>&& std::is_nothrow_constructible_v<T, Args...>)
        : leftValue_(std::forward<Args>(args)...), rightValue_ {leftValue_}
    {
        juce::ignoreUnused(tag);
    }

    /**
     * @internal Need a use-case for these. It seems that you would never want
     * to move/copy/swap the full LeftRight instance but rather apply those
     * operations to the encapsulated instance, in which case the relevant
     * operation is accessed via modify().
     */
    BasicLeftRight(const BasicLeftRight& other) = delete;
    BasicLeftRight(BasicLeftRight&& other)      = delete;
    auto operator=(const BasicLeftRight& rhs) -> BasicLeftRight& = delete;
    auto operator=(BasicLeftRight&& rhs) -> BasicLeftRight& = delete;
    void swap(BasicLeftRight& other) noexcept               = delete;

    /**
     * Modify the state of the managed data-structure
     *
     * Blocks/is-blocked-by other concurrent writers; does not
     * block concurrent readers
     *
     * This function requires that execution of the supplied functor
     * be noexcept.
     *
     * The function passed will be executed twice and *must*
     * result in the exact same mutation operation being applied
     * in both cases. For example it would be incorrect to supply
     * a function here that inserted a random number into the
     * underlying data-structure if said random number were calculated
     * for each invocation (i.e. each invocation would insert a
     * different value).
     *
     * @throws std::system_error on failure to lock internal mutex
     *
     * @internal I wanted the declaration to be as below so that this
     *           function doesn't even exist for non-noexcept functors,
     *           but g++ has not yet implemented noexcept mangling
     *           as of version 5.2.1. Instead we just static_assert the
     *           noexcept-ness of the functor in the body of the function
     *
     * template <typename F>
     * auto modify(F f)
     *     -> typename std::enable_if<noexcept(f(std::declval<T&>())),
     *             typename std::result_of<F(T&)>::type>::type;
     */
    template<typename F>
    auto modify(F f) -> std::invoke_result_t<F, value_type&>
    {
        static_assert(noexcept(f(std::declval<T&>())), "Modify functor must be noexcept");

        std::unique_lock<std::mutex> lock(writeMutex_);
        if (ReadPosition::Left == readPosition_.load(std::memory_order_relaxed))
        {
            f(rightValue_);
            readPosition_.store(ReadPosition::Right, std::memory_order_release);
            toggleReaderRegistry(lock);
            return f(leftValue_);
        }

        f(leftValue_);
        readPosition_.store(ReadPosition::Left, std::memory_order_release);
        toggleReaderRegistry(lock);
        return f(rightValue_);
    }

    /**
     * Observe the state of the managed data-structure
     *
     * Always wait-free provided ReaderRegistry::arrive() and
     * ReaderRegistry::depart() are truly wait-free
     *
     * @throws Whatever the provided functor throws and nothing else
     */
    template<typename F>
    auto observe(F f) const noexcept(noexcept(f(std::declval<value_type const&>())))
        -> std::invoke_result_t<F, value_type const&>
    {
        std::size_t idx = registryIndex_.load(std::memory_order_acquire);
        ScopedReadIndication sri(readerRegistries_[idx]);
        return ReadPosition::Left == readPosition_.load(std::memory_order_acquire) ? f(leftValue_) : f(rightValue_);
    }

private:
    class ScopedReadIndication
    {
    public:
        explicit ScopedReadIndication(ReaderRegistry& rr) noexcept : registry_ {rr} { registry_.arrive(); }
        ~ScopedReadIndication() noexcept { registry_.depart(); }

    private:
        ReaderRegistry& registry_;
    };

    template<typename Lock>
    void toggleReaderRegistry(Lock& lock) noexcept
    {
        jassert(lock.owns_lock());
        juce::ignoreUnused(lock);

        const std::size_t current = registryIndex_.load(std::memory_order_acquire);
        const std::size_t next    = (current + 1) & 0x1;

        while (!readerRegistries_[next].empty()) { std::this_thread::yield(); }

        registryIndex_.store(next, std::memory_order_release);

        while (!readerRegistries_[current].empty()) { std::this_thread::yield(); }
    }

    enum class ReadPosition
    {
        Left,
        Right
    };

    std::array<ReaderRegistry, 2> mutable readerRegistries_ {};

    std::atomic_size_t registryIndex_ {0};

    std::atomic<ReadPosition> readPosition_ {ReadPosition::Left};

    MC_ALIGNAS(HardwareCacheLineSize) value_type leftValue_;
    MC_ALIGNAS(HardwareCacheLineSize) value_type rightValue_;
    std::mutex writeMutex_ {};
};

/**
 * Simple implementation of ReaderRegistry concept
 *
 * This implementation is wait-free but readers will contend
 * on a single cache line due to the use of a shared counter.
 */
class AtomicReaderRegistry
{
public:
    void arrive() noexcept { counter_.fetch_add(1, std::memory_order_acq_rel); }
    void depart() noexcept { counter_.fetch_sub(1, std::memory_order_acq_rel); }
    [[nodiscard]] auto empty() const noexcept -> bool { return 0 == counter_.load(std::memory_order_acquire); }

private:
    std::atomic_uint_fast32_t counter_ {0};
} MC_ALIGNAS(HardwareCacheLineSize);

/**
 * Distributed implementation of ReaderRegistry
 *
 * Uses an array of N counters (suitably padded) and hashes reader
 * thread ids to indices into said array so that concurrent reader
 * registration can be made unlikely to contend. The likelihood
 * of a collision is dependent on the number of concurrent readers
 * relative to N.
 *
 * arrive() and depart() will perform better if N is a power of two.
 */
template<std::size_t N, typename HashFunc = std::hash<std::thread::id>>
class DistributedAtomicReaderRegistry
{
public:
    void arrive() noexcept
    {
        std::size_t index = HashFunc()(std::this_thread::get_id()) % N;
        counters_[index].incr();
    }

    void depart() noexcept
    {
        std::size_t index = HashFunc()(std::this_thread::get_id()) % N;
        counters_[index].decr();
    }

    [[nodiscard]] auto empty() const noexcept -> bool
    {
        bool value = std::none_of(begin(counters_), end(counters_), [](auto const& ctr) { return ctr.relaxedRead(); });
        std::atomic_thread_fence(std::memory_order_acquire);
        return value;
    }

private:
    class Counter
    {
    public:
        void incr() noexcept { value_.fetch_add(1, std::memory_order_acq_rel); }
        void decr() noexcept { value_.fetch_sub(1, std::memory_order_acq_rel); }
        [[nodiscard]] auto relaxedRead() const noexcept -> std::uint_fast32_t
        {
            return value_.load(std::memory_order_relaxed);
        }

    private:
        std::atomic_uint_fast32_t value_ {0};
    } MC_ALIGNAS(HardwareCacheLineSize);

    std::array<Counter, N> counters_ {};
} MC_ALIGNAS(HardwareCacheLineSize);

/**
 * Default LeftRight uses the simpler reader registry; prefer
 * DistributedAtomicReaderRegistry when reads are highly contended.
 */
template<typename T>
using LeftRight = BasicLeftRight<T, AtomicReaderRegistry>;

}  // namespace mc
#endif  // MODERN_CIRCUITS_JUCE_MODULES_LEFT_RIGHT_HPP
