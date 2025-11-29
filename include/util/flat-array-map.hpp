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

	FlatArrayMap(std::initializer_list<value_type> init) : mapSize(init.size()) {
		assert(mapSize <= N && "Attempting to assign initializer list that is bigger than FlatArrayMap");
		std::copy(init.begin(), init.end(), map.begin());
		std::sort(map.begin(), map.end());
	}

	// Lookup

	T& at(const Key& key) {
		size_t index = binary_search(key);
		assert(index != -1 && "Key was not found in map");
		return map[index].second;
	}
	const T& at(const Key& key) const { return at(key); }

	T& operator[](const Key& key) {
		size_t index = binary_search(key);
		if(index != -1) {
			return map[index].second;
		}
		else {
			insert({key, T()});
			return operator[](key);
		}
	}
	const T& operator[](const Key& key) const { return at(key); }

	T* find(const Key& key) {
		size_t index = binary_search(key);
		if (index != -1) return &map[index].second;
		else return nullptr;
	}
	const T* find(const Key& key) const { return find(key); }
	
	bool contains(const Key& key) const { return binary_search(key) != -1; }

	// Capacity
	
	size_t size() const { return mapSize; }
	size_t max_size() const { return N; }
	bool empty() const { return mapSize == 0; }

	// Modifiers

	void insert(const_reference pair) {
		if (mapSize == N) return;

		size_t insertionIndex = binary_search_leftmost(pair.first);

		for (size_t end = mapSize - 1; end >= insertionIndex; end--)
			map[end] = map[end - 1];

		map[insertionIndex] = pair;
		++mapSize;
	}

	void clear() { mapSize = 0; }

private:
	std::size_t binary_search(const Key& key) const {
		size_t L = 0;
		size_t R = mapSize;

		while ( L <= R ) {
			size_t mid = (L + R) / 2;

			if (map[mid].first == key) return mid;
			if (map[mid].first < key) L = mid + 1;
			else R = mid - 1; 
		}

		return -1;
	};

	std::size_t binary_search_leftmost(const Key& key) const {
		size_t L = 0;
		size_t R = mapSize;

		while ( L < R ) {
			size_t mid = (L + R) / 2;

			if (map[mid].first < key) L = mid + 1;
			else R = mid; 
		}

		return L;
	};

private:
	size_t mapSize = 0;
	std::array<value_type, N> map;
};

#endif
