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

        if (!canAccessDirectory(rootPath)) {
            throw std::runtime_error("Нет доступа для чтения корневой директории: " + path);
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
    auto options = std::filesystem::directory_options::skip_permission_denied;
    std::vector<std::thread> threads;

    const size_t maxThreads = std::thread::hardware_concurrency();
    std::atomic<size_t> activeThreads{ 0 };
    std::mutex cvMutex;
    std::condition_variable cv;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory, options)) {

        if (entry.is_regular_file()) {
            std::unique_lock<std::mutex> lock(cvMutex);
            cv.wait(lock, [&]() { return activeThreads < maxThreads; });

            activeThreads++;
           
            threads.emplace_back([this, path = entry.path().string(), &activeThreads, &cv]() {//emplace_back - прямое создание , а не перемещение, копирование как в push_back
            try {

                FileHandler fileHandler(database, logger, report);//
                fileHandler.processFile(path);//
            }
            catch (const std::exception& e) {
                // не прерывая дргие потоки делаем лог
                logger.logError("Ошибка обработки файла " + path + ": " + e.what());
            }
            activeThreads--;
            cv.notify_one(); // разблокировка ожидаюих потокв
            });

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


