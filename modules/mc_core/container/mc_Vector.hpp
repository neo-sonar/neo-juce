#ifndef MODERN_CIRCUITS_JUCE_MODULES_VECTOR_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_VECTOR_HPP

#include <boost/container/small_vector.hpp>

namespace mc {

template <typename T, std::size_t Capacity>
using SmallVector = boost::container::small_vector<T, Capacity>;

}

#endif // MODERN_CIRCUITS_JUCE_MODULES_VECTOR_HPP
