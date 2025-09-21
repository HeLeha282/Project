#include "Application.h"
#include "Database.h"
#include "HashCalculator.h"
#include <iostream>

Report Application::run(const std::string& base, const std::string& log, const std::string& path)
{
	Report report;
	Database database;
	database.load(base);
	std::string verdict = database.isMalicious("d6204ffeb36d2320e52f1d551cfa370");
	if (verdict.empty())
	{
		std::cout << "verdict empty àâàûïïððï";
	}
	else {
		std::cout << "verdict = " << verdict;
	}


	HashCalculator hashCalculator;
	std::cout<<hashCalculator.calcHash("C:\\Users\\Lesha\\Documents\\FPSMonitor.txt");



	
	return report;
}


