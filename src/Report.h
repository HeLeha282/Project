#ifndef REPORT_H
#define REPORT_H

#ifdef SCANNER_LIBRARY_EXPORTS
#define SCANNER_API __declspec(dllexport)
#else
#define SCANNER_API __declspec(dllimport)
#endif
#include <atomic>

class SCANNER_API Report {
public:
    void addFileProcessed();
    void addInfected();
    void addHealthy();
    void addError();
    void setElapsedTime(double seconds);
    void printReport();
    Report();
    Report(Report&& other) noexcept;

private:
    std::atomic<int> totalFiles{ 0 };
    std::atomic<int> infectedFiles{ 0 };
    std::atomic<int> healthyFiles{ 0 };
    std::atomic<int> errors{ 0 };
    double elapsedTime = 0.0;
};
#endif // !REPORT_H