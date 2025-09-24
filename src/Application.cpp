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
	Report report;
	Database database(base);
	Logger logger(log);
	DirectoryScanner scanner(database, logger, report);
	scanner.scan(path);

	return report;  // здесь компилятор применяет RVO и возвращает через переопределенный конструктор
}


