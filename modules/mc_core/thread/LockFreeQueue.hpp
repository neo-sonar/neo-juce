#pragma once

namespace mc {
template <typename T>
using LockFreeQueue = moodycamel::ConcurrentQueue<T>;

}