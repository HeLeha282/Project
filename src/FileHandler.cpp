#include "fileHandler.h"
#include "ios"
#include "fstream"
#include <iostream>
#include "HashCalculator.h"

FileHandler::FileHandler(Database& base, Logger& logger, Report& report) : database(base), logger(logger), report(report) {}

void FileHandler::processFile(const std::string& filePath)
{
    //Если не получится открыть то и хеш не посчитаем
    report.addFileProcessed();//добавляем "всего обработнных файлов"
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        //std::cerr << "Нет прав на чтение файла: " << filePath << std::endl;
        report.addError();//добоавляем "ошибка доступа" 
        
        logger.logError("Нет прав на чтение файла: " + filePath);
        return;
    }
    std::string hash = HashCalculator::calcHash(file);
    std::cout << filePath + "\n" + hash + "\n" + "----------------------------------------------------------------------------------------------------------------------------"<<std::endl;
    std::string verdict = database.getVerdict(hash);
    if (verdict != "") {
        report.addInfected();
        logger.logDetection(filePath, hash, verdict);
    }else{
        report.addHealthy();
    }
    logger.logInfo("есть права на чтение файла: " + filePath);
}