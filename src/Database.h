#pragma once
#include <unordered_map>
#include <string>

class Database{
public:
	Database(const std::string& csvFilePath);
	std::string getVerdict(std::string hash);
private:
	void load(const std::string& csvFilePath);

	std::unordered_map<std::string, std::string> maliciousHashes;
};