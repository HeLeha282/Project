#include <gtest/gtest.h>
#include "Report.h"

TEST(ReportTest, CountersIncrementCorrectly) {
    Report report;

    report.addFileProcessed();
    report.addInfected();
    report.addHealthy();
    report.addError();

    // ѕровер€ем через публичные методы (если добавить getters)
    // »ли тестируем через printReport() вывод
}

TEST(ReportTest, ThreadSafeIncrements) {
    Report report;

    // Ёмулируем многопоточное добавление
    std::vector<std::thread> threads;
    for (int i = 0; i < 100; ++i) {
        threads.emplace_back([&report]() {
            report.addFileProcessed();
            report.addHealthy();
            });
    }

    for (auto& t : threads) t.join();

    // ƒолжно быть 100 * 2 = 200
}