#ifndef RANDOM_H_
#define RANDOM_H_

#include <cstdlib>

void InitRandom();
void InitRandom(unsigned seed);

inline float UnitRandom()
{
	return std::rand() / (RAND_MAX + 1.0f);
}

inline int RandomInt(int upper)
{
	return (int)(upper * UnitRandom());
}

inline int RandomInt(int lower, int upper)
{
	return lower + (int)((upper - lower) * UnitRandom());
}


inline float RandomFloat(float lower, float upper)
{
	return lower + (upper - lower) * UnitRandom();
}

inline int RandomSign()
{
	return UnitRandom() < 0.5f ? 1 : -1;
}

inline float UnitRandomInclusive()
{
	return rand() / (float)RAND_MAX;
}

inline int RandomIntInclusive(int lower, int upper)
{
	return lower + (int)((upper - lower + 1) * UnitRandom());
}

inline float RandomFloatInclusive(float lower, float upper)
{
	return lower + (upper - lower) * UnitRandomInclusive();
}

#endif