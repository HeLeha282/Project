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
	std::cout << "\n=== SCAN REPORT ===\n";
	std::cout << "Total files processed: " << totalFiles << "\n";
	std::cout << "Infected files found: " << infectedFiles << "\n";
	std::cout << "Errors encountered: " << errors << "\n";

	std::cout << "Time elapsed: " << std::fixed << std::setprecision(1)
		<< elapsedTime << " seconds\n";
}
