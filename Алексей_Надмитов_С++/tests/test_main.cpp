#include <gtest/gtest.h>
#include "FileHandler.h"
#include "Database.h"
#include "Logger.h"
#include "Report.h"
#include <fstream>

class IntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // тестовые файлы
        std::ofstream hash_db("test_db.csv");
        hash_db << "5d41402abc4b2a76b9719d911017c592;TestVirus\n";
        hash_db.close();

        std::ofstream test_file("test_file.txt");
        test_file << "hello"; // md5 = 5d41402abc4b2a76b9719d911017c592
        test_file.close();
    }
};

TEST_F(IntegrationTest, FileHandlerDetectsInfectedFile) {
    Database db("test_db.csv");
    Logger logger("test.log");
    Report report;

    FileHandler handler(db, logger, report);
    handler.processFile("test_file.txt");

    // Проверяем результаты
    ASSERT_EQ(report.getTotalFiles(), 1); // нужен геттер в Report
    ASSERT_EQ(report.getInfectedFiles(), 1); // нужен геттер
}