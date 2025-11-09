#ifndef CYCLIC_INTEGER_H
#define CYCLIC_INTEGER_H
#include <stdint.h>

/// @brief an `int8_t` which stores and cycles values between [ `min` , `max` )
struct CyclicInt8_t {
	int8_t value;
	int8_t min;
	int8_t max;

	CyclicInt8_t(int8_t min, int8_t max, int value = 0)
		: value(value),
			min(min),
			max(max)
	{};

	inline CyclicInt8_t& operator++() {
		value = (value + 1) % max;
		return *this;
	}

	inline void operator--() {
		value = value - 1 < min ? max : value - 1;
	}
};

#endif
