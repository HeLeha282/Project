#pragma once
#include <string>
#include <fstream>
#include <chrono>

class Logger {
private:
    std::ofstream log_file;

public:
    Logger(const std::string& filename);

    void logDetection(const std::string& file_path, const std::string& hash,
        const std::string& verdict);
    
    //ѕока что не знаю, будет это реализованно через параметр (если есть разные причины почему файл не открылс€). 
    // »ли без параметра (текст константа будет в методе)
    void logError(const std::string& error);


    //могу вывести какую то служебную информацию
    //[INFO] 2024-01-15 14:30:25.123 | Scan started: path="C:\target_folder" base="malware_db.csv"
    //[INFO] 2024 - 01 - 15 14:30 : 25.124 | Threads : 4 | Recursive : true
    void logInfo(const std::string& message);

    ~Logger();
};