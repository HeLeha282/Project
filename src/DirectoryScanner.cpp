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

bool DirectoryScanner::canAccessDirectory(const std::filesystem::path& dir)
{
    std::error_code ec;
    std::filesystem::directory_iterator it(dir, ec);
    if (ec) {
        // Ошибка доступа
        std::cerr << "Нет прав доступа к " << dir << ": " << ec.message() << std::endl;
        return false;
    }
    return true;
}

void DirectoryScanner::scanDirectory(const std::filesystem::path& directory)
{

    auto options = std::filesystem::directory_options::skip_permission_denied;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory, options)) {
        std::cout << entry.path().filename().string() << std::endl;

        if (entry.is_regular_file()) {
            std::cout << entry.path().filename().string() << std::endl;//для файлов второй раз вывожу

            std::ifstream inf(entry.path());
            if (inf.is_open()) {
                std::string str;
                inf >> str;
                if (inf.bad()) {
                    std::cout << "с потоком проблемка" << std::endl;
                }
                inf.close();
                std::cout << "поток закрыт" << std::endl;
            }
            else {
                std::cout << "Не удалось открыть файл" << std::endl;
            }
        }
        else {
            if (canAccessDirectory(entry.path())) {
                std::cout << "Доступ есть" << std::endl;
            }
            else {
                std::cout << "Доступа нет" << std::endl;
            }
        }
        std::cout << "--------------------------------------" << std::endl;
    }
}