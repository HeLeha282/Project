#ifndef REPORT_H
#define REPORT_H

class Report {
public:
    void addFileProcessed();
    void addInfected();
    void addError();
    void setElapsedTime(double seconds);
private:
    int totalFiles = 0;
    int infectedFiles = 0;
    int errors = 0;
    double elapsedTime;
};

#endif // !REPORT_H