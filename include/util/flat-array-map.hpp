#ifndef FLAT_ARRAY_MAP_H
#define FLAT_ARRAY_MAP_H
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <utility>

template<typename Key, typename T, std::size_t N>
class FlatArrayMap {
public:
	using value_type = std::pair<Key, T>;
	using reference = value_type&;
	using const_reference = const value_type&;

	// Initialization

	FlatArrayMap() = default;

	FlatArrayMap(std::initializer_list<value_type> init) : currentSize(init.size()) {
		assert(currentSize <= N && "Attempting to assign initializer list that is bigger than FlatArrayMap");
		std::copy(init.begin(), init.end(), map.begin());
		std::sort(map.begin(), map.begin() + currentSize);
	}

	// Lookup

	T& at(const Key& key) {
		int index = binary_search(key);
		assert(index != -1 && "Key was not found in map");
		return map[index].second;
	}
	const T& at(const Key& key) const {
		int index = binary_search(key);
		assert(index != -1 && "Key was not found in map");
		return map[index].second;
	}

	T& operator[](const Key& key) {
		int index = binary_search(key);

		if(index == -1) {
			assert(currentSize < N && "Map at max capacity, could not store key");
			insert({key, T()});
			return at(key);
		}
		else {
			return map[index].second;
		}
	}
	const T& operator[](const Key& key) const { return at(key); }

	T* find(const Key& key) {
		int index = binary_search(key);
		if (index == -1) return nullptr;
		return &map[index].second;
	}
	const T* find(const Key& key) const {
		int index = binary_search(key);
		if (index == -1) return nullptr;
		return &map[index].second;
	}
	
	bool contains(const Key& key) const { return binary_search(key) != -1; }

	// Capacity
	
	size_t size() const { return currentSize; }
	size_t max_size() const { return N; }
	bool empty() const { return currentSize == 0; }

	// Modifiers

	void insert(const_reference pair) {
		if (currentSize == N) return;
		int insertionIndex = binary_search_leftmost(pair.first);

		for (int end = currentSize; end > insertionIndex; end--)
			map[end] = map[end - 1];

		map[insertionIndex] = pair;
		++currentSize;
	}

	void clear() { currentSize = 0; }

private:
	int binary_search(const Key& key) const {
		int L = 0;
		int R = currentSize - 1;

		while ( L <= R ) {
			int mid = (L + R) / 2;

			if (map[mid].first == key) return mid;
			if (map[mid].first < key) L = mid + 1;
			else R = mid - 1; 
		}

		return -1;
	};

	int binary_search_leftmost(const Key& key) const {
		int L = 0;
		int R = currentSize;

		while ( L < R ) {
			int mid = (L + R) / 2;

			if (map[mid].first < key) L = mid + 1;
			else R = mid; 
		}

		return L;
	};

private:
	size_t currentSize = 0;
	std::array<value_type, N> map;
};

#endif
