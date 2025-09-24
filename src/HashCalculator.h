#ifndef HASH_CALCULATOR_H
#define HASH_CALCULATOR_H
#include <string>

class HashCalculator {
public:
	std::string static calcHash(std::ifstream& file);
};

#endif // !HASH_CALCULATOR_H