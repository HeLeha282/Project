#include "Logger.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>

Logger::Logger(const std::string& filename)
{
    log_file.open(filename);
    if (!log_file.is_open()) {
        throw std::runtime_error("Cannot open log file: " + filename);
    }
}

void Logger::logDetection(const std::string& file_path, const std::string& hash, const std::string& verdict)
{
    std::lock_guard<std::mutex> lock(log_mutex);
    auto now = std::chrono::system_clock::now();//не потокобезопасно
    auto time_t = std::chrono::system_clock::to_time_t(now);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time_t));

    try {
        log_file << "[DETECTED] "
            << buffer << " | "
            << "File: " << file_path << " | "
            << "Hash: " << hash << " | "
            << "Verdict: " << verdict
            << std::endl;
    }
    catch (const std::ios_base::failure& e) {
        // Диск переполнен, нет прав записи и т.д.
        throw std::ios_base::failure("Ошибка записи в лог: " + std::string(e.what()));
    }
}

void Logger::logError(const std::string& error)
{
    std::lock_guard<std::mutex> lock(log_mutex);
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time_t));

    try {
    log_file << "[ERROR] "
        << buffer << " | "
        << "Error: " << error
        << std::endl;
}
    catch (const std::ios_base::failure& e) {
        // Диск переполнен, нет прав записи и т.д.
        throw std::ios_base::failure("Ошибка записи в лог: " + std::string(e.what()));
    }
}

void Logger::logInfo(const std::string& message)
{
    std::lock_guard<std::mutex> lock(log_mutex);
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time_t));

    try {
    log_file << "[INFO] "
        << buffer << " | "
        << message
        << std::endl;
}
    catch (const std::ios_base::failure& e) {
        // Диск переполнен, нет прав записи и т.д.
        throw std::ios_base::failure("Ошибка записи в лог: " + std::string(e.what()));
    }
}

Logger::~Logger()
{
    if (log_file.is_open()) {
        log_file.close();
    }
}

