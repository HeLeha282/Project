#include "Report.h"
#include <iostream>
#include <chrono>
#include <iomanip>
void Report::addFileProcessed()
{
	totalFiles += 1;
}

void Report::addInfected()
{
	infectedFiles += 1;
}

void Report::addHealthy()
{
	healthyFiles += 1;
}

void Report::addError()
{
	errors += 1;
}

void Report::setElapsedTime(double seconds)
{
	elapsedTime = seconds;
}

void Report::printReport()
{
	std::cout << "\n===== SCAN REPORT =====\n";
	std::cout << "Total files processed: " << totalFiles.load() << "\n";//load явно чиатет атомарные значения
	std::cout << "Infected files found: " << infectedFiles.load() << "\n";
	std::cout << "Healthy files found: " << healthyFiles.load() << "\n";
	std::cout << "Errors encountered: " << errors.load() << "\n";
	std::cout << "Time elapsed: " << std::fixed << std::setprecision(2)
		<< elapsedTime << " seconds\n";
}

Report::Report()
{
}

Report::Report(Report&& other) noexcept : totalFiles(other.totalFiles.load())
, infectedFiles(other.infectedFiles.load())
, healthyFiles(other.healthyFiles.load())
, errors(other.errors.load())
, elapsedTime(other.elapsedTime)
{}
