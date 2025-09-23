#include "fileHandler.h"
#include "ios"
#include "fstream"
#include <iostream>
#include "HashCalculator.h"

FileHandler::FileHandler(Database& base, Logger& logger, Report& report) : database(base), logger(logger), report(report) {}

void FileHandler::processFile(const std::string& filePath)
{
    report.addFileProcessed();//��������� "����� ����������� ������"
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        //std::cerr << "��� ���� �� ������ �����: " << filePath << std::endl;
        report.addError();//���������� "������ �������" 
        
        logger.logError("��� ���� �� ������ �����: " + filePath);
        return;
    }
    std::string hash = HashCalculator::calcHash(file);
    std::string verdict = database.getVerdict(hash);
    if (verdict != "") {
        report.addInfected();
        logger.logDetection(filePath, hash, verdict);
    }
    logger.logInfo("���� ����� �� ������ �����: " + filePath);
}