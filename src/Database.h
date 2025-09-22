#pragma once
#include <unordered_map>
#include <string>

class Database {
public:
	void load(const std::string& csvFilePath);
	std::string getVerdict(std::string hash);
private:
	std::unordered_map<std::string, std::string> maliciousHashes;
};