#ifndef MODERN_CIRCUITS_APP_ZENTRALE_THREAD_SAFE_QUEUE_HPP
#define MODERN_CIRCUITS_APP_ZENTRALE_THREAD_SAFE_QUEUE_HPP

#include <mutex>
#include <queue>

namespace mc
{
template<typename T>
class ThreadSafeQueue
{

public:
    using value_type = T;
    using size_type  = typename std::queue<T>::size_type;

    ThreadSafeQueue()  = default;
    ~ThreadSafeQueue() = default;

    ThreadSafeQueue(ThreadSafeQueue const&) = delete;
    auto operator=(ThreadSafeQueue const&) -> ThreadSafeQueue& = delete;

    ThreadSafeQueue(ThreadSafeQueue&& other) = delete;
    auto operator=(ThreadSafeQueue&&) -> ThreadSafeQueue& = delete;

    [[nodiscard]] auto pop() -> boost::optional<value_type>
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) { return boost::make_optional(false, value_type {}); }
        value_type tmp = queue_.front();
        queue_.pop();
        return tmp;
    }

    auto push(value_type const& item) -> void
    {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
    }

    auto push(value_type&& item) -> void
    {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(item));
    }

    [[nodiscard]] auto size() const -> size_type
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

private:
    // Moved out of public interface to prevent races between this and pop().
    [[nodiscard]] auto empty() const -> bool { return queue_.empty(); }

    std::queue<value_type> queue_;
    std::mutex mutable mutex_;
};
}  // namespace mc

#endif  // MODERN_CIRCUITS_APP_ZENTRALE_THREAD_SAFE_QUEUE_HPP
