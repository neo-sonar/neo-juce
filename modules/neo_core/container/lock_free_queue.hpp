#pragma once

namespace neo {

template <typename T>
using LockFreeQueue = moodycamel::ConcurrentQueue<T>;

}
