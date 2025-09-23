#include "Logger.h"
#include <stdexcept>
#include <iostream>

Logger::Logger(const std::string& filename)
{
    log_file.open(filename);
    if (!log_file.is_open()) {
        throw std::runtime_error("Cannot open log file: " + filename);
    }
}

void Logger::logDetection(const std::string& file_path, const std::string& hash, const std::string& verdict)
{
    
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);

    log_file << "[DETECTED] "
        << std::localtime(&time_t) << " | "
        << "File: " << file_path << " | "
        << "Hash: " << hash << " | "
        << "Verdict: " << verdict
        << std::endl;
}

void Logger::logError(const std::string& error)
{
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);

    log_file << "[ERROR] "
        << std::localtime(&time_t) << " | "
        << "Error: " << error
        << std::endl;
}

void Logger::logInfo(const std::string& message)
{
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);

    log_file << "[INFO] "
        << std::localtime(&time_t) << " | "
        << message
        << std::endl;
}

Logger::~Logger()
{
    //std::cout << "Logger Destruct"<< std::endl;
    if (log_file.is_open()) {
        log_file.close();
    }
}

