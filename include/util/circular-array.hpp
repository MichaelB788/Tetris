#ifndef CIRCULAR_ARRAY_H
#define CIRCULAR_ARRAY_H
#include <cstddef>
#include <iterator>

template<typename T, std::size_t N>
class CircularArray {
public:
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using const_reference = const T&;
	using const_pointer = const T*;

	reference front() { return data[head]; };
	const_reference front() const { return data[head]; };
	reference back() { return data[tail]; };
	const_reference back() const { return data[tail]; };

	std::size_t size() const { return N; }

	void push_back(const value_type& value) { tail = (tail + 1) % N; m_data[tail] = value; }
	void pop_front();

	void push_front(const value_type& value);
	void pop_back();
	
	struct iterator {
		using iterator_category = std::contiguous_iterator_tag;
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
		using iterator_category = std::contiguous_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using const_value_type = const T;
		using const_pointer = const T*;
		using const_reference = const T&;

		const_iterator(const pointer x) : p(x) {}

		const_reference operator*() const { return *p; }
		const_pointer operator->() const { return p; }

		const_iterator& operator++() { p = (p + 1) % N; return *this; }
		const_iterator operator++(int) { const_iterator tmp = *this; operator++(); return tmp; }

		bool operator==(const iterator& rhs) const { return p == rhs.p; }
		bool operator!=(const iterator& rhs) const { return p != rhs.p; }

	private:
		const pointer p;
	};

	iterator begin() { return iterator(&data[head]); }
	iterator end() { return iterator(&data[tail]); }
	const_iterator begin() const { return const_iterator(&data[head]); }
	const_iterator end() const { return const_iterator(&data[tail]); }
	const_iterator cbegin() const { return const_iterator(&data[head]); }
	const_iterator cend() const { return const_iterator(&data[tail]); }

private:
	int head = 0;
	int tail = head;
	T data[N];
};

#endif
