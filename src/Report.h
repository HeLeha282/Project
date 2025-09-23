#ifndef REPORT_H
#define REPORT_H

class Report {
public:
    void addFileProcessed();
    void addInfected();
    void addHealthy();
    void addError();
    void setElapsedTime(double seconds);
    void printReport();

private:
    int totalFiles = 0;
    int infectedFiles = 0;
    int healthyFiles;
    int errors = 0;
    double elapsedTime = 0.0;
};

#endif // !REPORT_H