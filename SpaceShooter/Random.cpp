#include "Random.h"

#include <ctime>

void InitRandom(){
	int i, n;

	std::srand((unsigned)std::time(NULL) ^ (unsigned)std::rand());

	n = 10 + rand() % 10;
	for (i = 0; i < n; i++){
		std::rand();
	}
}

void InitRandom(unsigned seed){
	std::srand(seed);
}