#pragma once

namespace neo {

template <typename T, std::size_t Capacity>
using StaticVector = boost::container::static_vector<T, Capacity>;

} // namespace neo
