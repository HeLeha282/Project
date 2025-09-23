#pragma once
#include <string>

class HashCalculator {
public:
	std::string static calcHash(std::ifstream& file);
};