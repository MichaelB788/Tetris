#include "util/ring-buffer.hpp"

template<typename T, std::size_t N>
void RingBuffer<T, N>::push(const value_type& value) {
	if ((write + 1) % N == read) return;
	data[write] = value;
	write = (write + 1) % N;
}
