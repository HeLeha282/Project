#include "Application.h"
#include "Database.h"
#include "HashCalculator.h"
#include "Logger.h"
#include <iostream>
#include "DirectoryScanner.h"
#include <fstream>

Report Application::run(const std::string& base, const std::string& log, const std::string& path)
{
	Report report;
	Database database(base);
	Logger logger(log);

	//database.load("C:\\Users\\Lesha\\Desktop\\TestTaskKaspersky\\Project\\build\\text.csv");
	//std::string verdict = database.getVerdict("ac6204ffeb36d2320e52f1d551cfa370");
	//if (verdict.empty())
	//{
	//	std::cout << "verdict empty àâàûïïððï" << '\n';
	//}
	//else {
	//	std::cout << "verdict = " << verdict << '\n';
	//}


	HashCalculator hashCalculator;
	std::string filePath = "C:\\Users\\Lesha\\Documents\\FPSMonitor.txt";
	std::ifstream ifstream(filePath, std::ios::binary);
	std::string hash = hashCalculator.calcHash(ifstream);
	std::string verdict = database.getVerdict(hash);
	report.addFileProcessed();
	if (!verdict.empty()) {
		report.addInfected();
		logger.logDetection(filePath, hash, verdict);
	}

	DirectoryScanner scanner(database, logger, report);
	scanner.scan("C:\\Users\\Lesha\\Desktop\\TestTaskKaspersky\\Project\\src\\AUE_BASOTA_LOL");


	return report;
}


