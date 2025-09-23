#pragma once
#include "Database.h"
#include "Logger.h"
#include "Report.h"
#include <string>

class FileHandler {
public:
	FileHandler(Database& base, Logger& logger, Report& report);
	void processFile(const std::string& filePath);
private:
	Database& database;
	Logger& logger;
	Report& report;
};

