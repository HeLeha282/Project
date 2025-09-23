#pragma once
#include <string>

class HashCalculator {
public:
	std::string static calcHash(const std::ifstream& ifstream);
};