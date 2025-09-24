#include <gtest/gtest.h>
#include "Report.h"

TEST(ReportTest, CountersIncrementCorrectly) {
    Report report;

    report.addFileProcessed();
    report.addInfected();
    report.addHealthy();
    report.addError();

    // ��������� ����� ��������� ������ (���� �������� getters)
    // ��� ��������� ����� printReport() �����
}

TEST(ReportTest, ThreadSafeIncrements) {
    Report report;

    // ��������� ������������� ����������
    std::vector<std::thread> threads;
    for (int i = 0; i < 100; ++i) {
        threads.emplace_back([&report]() {
            report.addFileProcessed();
            report.addHealthy();
            });
    }

    for (auto& t : threads) t.join();

    // ������ ���� 100 * 2 = 200
}