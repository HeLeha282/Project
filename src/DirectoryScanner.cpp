#include "DirectoryScanner.h"
#include <iostream>
#include <filesystem>


DirectoryScanner::DirectoryScanner(Database& base, Logger& logger, Report& report) : database(base), logger(logger), report(report) {}//в списке инициализации потому что ссылки

void DirectoryScanner::scan(std::string path)
{
    try {
        std::filesystem::path rootPath(path);

        if (!std::filesystem::exists(rootPath)) {
            throw std::runtime_error("Directory does not exist: " + path);
        }

        if (!std::filesystem::is_directory(rootPath)) {
            throw std::runtime_error("Path is not a directory: " + path);
        }

        scanDirectory(rootPath);

    }
    catch (const std::filesystem::filesystem_error& e) {
        logger.logError(path, std::string(e.what()));
        throw;//это ловит main
    }
}

void DirectoryScanner::scanDirectory(const std::filesystem::path& directory)
{
    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
            std::cout << entry.path().filename().string() << std::endl;
            if (entry.is_regular_file()) {
                std::cout << entry.path().filename().string() << std::endl;
            }
            std::cout << "--------------------------------------" << std::endl;
        }
    }
    catch (const std::filesystem::filesystem_error& ex) {
        std::cerr << "Ошибка доступа к файловой системе: " << ex.what() << std::endl;
    } 
}
