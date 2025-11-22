#ifndef RING_BUFFER_H
#define RING_BUFFER_H
#include <cassert>
#include <cstddef>
#include <iterator>

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

	// Element access

	reference peek() { assert( !empty() && "Ring buffer has no elements"); return data[read]; };
	const_reference peek() const { assert( !empty() && "Ring buffer has no elements"); return data[read]; };

	// Capacity

	std::size_t size() const { return (read - write + N) % N; }
	std::size_t max_size() const { return N - 1; }
	bool empty() const { return read == write; }

	// Modifiers

	void push(const value_type& value);
	void pop() { if ( read != write ) read = (read + 1) % N; }
	
	// Iterators

	struct iterator {
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		iterator(pointer x) : p(x) {}

		reference operator*() { return *p; }
		pointer operator->() { return p; }

		iterator& operator++() { p = (p + 1) % N; return *this; }
		iterator operator++(int) { iterator tmp = *this; operator++(); return tmp; }

		bool operator==(const iterator& rhs) const { return p == rhs.p; }
		bool operator!=(const iterator& rhs) const { return p != rhs.p; }

	private:
		pointer p;
	};

	struct const_iterator {
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using const_value_type = const T;
		using const_pointer = const T*;
		using const_reference = const T&;

		const_iterator(const pointer x) : p(x) {}

		const_reference operator*() const { return *p; }
		const_pointer operator->() const { return p; }

		const_iterator& operator++() { p = (p + 1) % N; return *this; }
		const_iterator operator++(int) { const_iterator tmp = *this; operator++(); return tmp; }

		bool operator==(const_iterator& rhs) const { return p == rhs.p; }
		bool operator!=(const_iterator& rhs) const { return p != rhs.p; }

	private:
		const pointer p;
	};

	iterator begin() { return iterator(&data[read]); }
	iterator end() { return iterator(&data[(write + 1) % N]); }

	const_iterator begin() const { return const_iterator(&data[read]); }
	const_iterator end() const { return const_iterator(&data[(write + 1) % N]); }

	const_iterator cbegin() const { return const_iterator(&data[read]); }
	const_iterator cend() const { return const_iterator(&data[(write + 1) % N]); }

private:
	int read = 0;
	int write = 0;
	T data[N];
};

#endif
