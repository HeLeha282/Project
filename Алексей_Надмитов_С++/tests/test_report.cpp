#include <gtest/gtest.h>
#include "Report.h"

TEST(ReportTest, CountersIncrementCorrectly) {
    Report report;

    report.addFileProcessed();
    report.addInfected();
    report.addHealthy();
    report.addError();

    ASSERT_EQ(report.getTotalFiles(), 1);
    ASSERT_EQ(report.getInfectedFiles(), 1);
    ASSERT_EQ(report.getHealthyFiles(), 1);
    ASSERT_EQ(report.getErrors(), 1);
}

TEST(ReportTest, ThreadSafeIncrements) {
    Report report;
    std::vector<std::thread> threads;

    for (int i = 0; i < 100; ++i) {
        threads.emplace_back([&report]() {
            report.addFileProcessed();
            report.addHealthy();
            });
    }

    for (auto& t : threads) t.join();

    ASSERT_EQ(report.getTotalFiles(), 100);
    ASSERT_EQ(report.getHealthyFiles(), 100);


    ASSERT_EQ(report.getInfectedFiles(), 0);
    ASSERT_EQ(report.getErrors(), 0);
}