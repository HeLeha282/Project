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
    catch (const std::runtime_error& e) {
        logger.logError(std::string(e.what()));
        throw;//это ловит main
    }
}

bool DirectoryScanner::canAccessDirectory(const std::filesystem::path& dir)
{
    std::error_code ec;
    std::filesystem::directory_iterator it(dir, ec);
    if (ec) {
        // Ошибка доступа
        //std::cerr << "Нет прав доступа к " << dir << ": " << ec.message() << std::endl;
        return false;
    }
    return true;
}

void DirectoryScanner::scanDirectory(const std::filesystem::path& directory)
{
    FileHandler fileHandler(database, logger, report);
    auto options = std::filesystem::directory_options::skip_permission_denied;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory, options)) {
        //std::cout << entry.path().filename().string() << std::endl;

        if (entry.is_regular_file()) {//fileHandler
            //std::cout << "Это файл" << std::endl;//для файлов второй раз вывожу
            fileHandler.processFile(entry.path().string());
        }
        else {
            if (!canAccessDirectory(entry.path())) {
                //std::cout << "Доступа нет" << std::endl;
                logger.logError("Нет доступа к папке " + entry.path().string());
            }
        }
        //std::cout << "--------------------------------------" << std::endl;
    }
}