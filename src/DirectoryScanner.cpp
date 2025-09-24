#include "DirectoryScanner.h"
#include <iostream>
#include <filesystem>

#include <thread>

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
        return false;
    }
    return true;
}

void DirectoryScanner::scanDirectory(const std::filesystem::path& directory)
{
    FileHandler fileHandler(database, logger, report);
    auto options = std::filesystem::directory_options::skip_permission_denied;
    std::mutex rofl_m;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory, options)) {

        if (entry.is_regular_file()) {
            //fileHandler.processFile(entry.path().string());
            threads.emplace_back([this, path = entry.path().string(), &rofl_m]() {//emplace_back - прямое создание , а не перемещение, копирование как в push_back
                FileHandler fileHandler(database, logger, report);//
                fileHandler.processFile(path, rofl_m);
                });
            //std::thread t(&FileHandler::processFile, fileHandler, entry.path().string());
            //t.join();
        }
        else {
            if (!canAccessDirectory(entry.path())) {
                logger.logError("Нет доступа к папке " + entry.path().string());
            }
        }
    }
    for (auto& t : threads) {
        t.join();
    }
}