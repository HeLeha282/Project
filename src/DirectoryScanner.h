#ifndef DIRECTORY_SCANNER_H
#define DIRECTORY_SCANNER_H
#include "Database.h"
#include "Logger.h"
#include "Report.h"
#include <string>
#include "fileHandler.h"
class DirectoryScanner {
public:
	DirectoryScanner(Database& base, Logger& logger, Report& report);
	void scan(std::string path);

private:
    std::vector<std::thread> threads;
    Database& database;
    Logger& logger;
    Report& report;
    bool canAccessDirectory(const std::filesystem::path& dir);
    void scanDirectory(const std::filesystem::path& directory);
};


#endif // !DIRECTORY_SCANNER_H