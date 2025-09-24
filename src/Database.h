#ifndef DATABASE_H
#define DATABASE_H
#include <unordered_map>
#include <string>
#ifdef SCANNER_LIBRARY_EXPORTS
#define SCANNER_API __declspec(dllexport)
#else
#define SCANNER_API __declspec(dllimport)
#endif
class SCANNER_API Database{
public:
	Database(const std::string& csvFilePath);
	std::string getVerdict(std::string hash);
private:
	void load(const std::string& csvFilePath);

	std::unordered_map<std::string, std::string> maliciousHashes;
};

#endif // !DATABASE_H