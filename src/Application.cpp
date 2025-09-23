#include "Application.h"
#include "Database.h"
#include "HashCalculator.h"
#include "Logger.h"
#include <iostream>
#include "DirectoryScanner.h"
#include <fstream>

#include <chrono>
#include <thread>

Report Application::run(const std::string& base, const std::string& log, const std::string& path)
{

	double seconds = 1.5; // 1.5 секунды
	std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
	Report report;
	Database database(base);
	Logger logger(log);
	DirectoryScanner scanner(database, logger, report);
	scanner.scan(path);

	return report;
}


