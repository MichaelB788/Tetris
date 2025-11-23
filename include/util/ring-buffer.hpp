#ifndef RING_BUFFER_H
#define RING_BUFFER_H
#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

/** @brief A fixed-size circular buffer template that stores up to N - 1 elements.
 *
 * This ring buffer uses a classic design where one slot is intentionally left unused
 * to distinguish between the "empty" and "full" states without requiring additional
 * tracking variables. The unused slot acts as a sentinel boundary.
 *
 * Design rationale:
 * - When writeIndx == readIndx, the buffer is empty.
 * - When (writeIndx + 1) % N == readIndx, the buffer is full.
 * - This approach avoids needing a separate counter or flag, keeping the logic simple.
 *
 * @tparam T The type of elements stored in the buffer.
 * @tparam N The total capacity of the underlying array (usable capacity is N - 1).
 *
 * @note If you need to store N elements and find the N - 1 limitation inconvenient,
 *       consider allocating an array of size N + 1 when constructing the buffer.
 *
 * @example
 * @code
 *   RingBuffer<int, 5> rb;  // Stores up to 4 integers
 *   rb.push(10);
 *   rb.push(20);
 *   int val = rb.peek();  // Retrieves 10
 * @endcode
 */
template<typename T, std::size_t N>
class RingBuffer {
public:
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using const_reference = const T&;
	using const_pointer = const T*;

	RingBuffer<T, N>() = default;

	RingBuffer<T, N>(std::initializer_list<T> init) {
		if (init.size() <= size()) { 
			std::copy(init.begin(), init.end(), data);
			write = init.size();
		}
		else throw std::length_error("Attempting to allocate more elements than is possible in RingBuffer");
	}

	// Element access

	reference peek() { return data[read]; };
	const_reference peek() const { return data[read]; };

	// Capacity

	std::size_t size() const { return (write - read + N) % N; }
	std::size_t max_size() const { return N - 1; }
	bool empty() const { return read == write; }

	// Modifiers

	void push(const value_type& value) {
		if ((write + 1) % N == read) return; data[write] = value; write = (write + 1) % N;
	}
	value_type pop() { if (read != write) { value_type ret = data[read]; read = (read + 1) % N; return ret; } }

	// Iterators

	struct iterator {
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = value_type*;
		using reference = value_type&;

		iterator(pointer base, size_t indx) : base(base), indx(indx) {}

		reference operator*() { return base[indx]; }
		pointer operator->() { return base[indx]; }

		iterator& operator++() { indx = (indx + 1) % N; return *this; }
		iterator operator++(int) { iterator tmp = *this; operator++(); return tmp; }

		friend bool operator==(const iterator& a, const iterator& b) { return a.base[a.indx] == b.base[b.indx]; }
		friend bool operator!=(const iterator& a, const iterator& b) { return a.base[a.indx] != b.base[b.indx]; }

		private:
		pointer base;
		size_t indx;
	};

	struct const_iterator {
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;

		const_iterator(pointer base, size_t indx) : base(base), indx(indx) {}

		const_reference operator*() const { return base[indx]; }
		const_pointer operator->() const { return base[indx]; }

		const_iterator& operator++() { indx = (indx + 1) % N; return *this; }
		const_iterator operator++(int) { const_iterator tmp = *this; operator++(); return tmp; }

		friend bool operator==(const const_iterator& a, const const_iterator& b) { return a.base[a.indx] == b.base[b.indx]; }
		friend bool operator!=(const const_iterator& a, const const_iterator& b) { return a.base[a.indx] != b.base[b.indx]; }

		private:
		const_pointer base;
		size_t indx;
	};

	iterator begin() { return iterator(data, read); }
	iterator end() { return iterator(data, write); }

	const_iterator cbegin() const { return const_iterator(data, read); }
	const_iterator cend() const { return const_iterator(data, write); }

private:
	int read = 0;
	int write = 0;
	T data[N];
};

#endif
