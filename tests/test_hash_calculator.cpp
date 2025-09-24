#include <gtest/gtest.h>
#include "HashCalculator.h"
#include <sstream>
#include <fstream>
#include <cstdio>

TEST(HashCalculatorTest, CalculatesCorrectMD5) {
    // Создаём временный файл
    std::ofstream tmpFile("tmp_test.txt");
    tmpFile << "hello world";
    tmpFile.close();

    std::ifstream file("tmp_test.txt");
    std::string hash = HashCalculator::calcHash(file);

    // Удаляем временный файл
    std::remove("tmp_test.txt");

    EXPECT_EQ(hash, "5eb63bbbe01eeed093cb22bb8f5acdc3");
}

TEST(HashCalculatorTest, HandlesEmptyFile) {
    std::stringstream file("");
    std::string hash = HashCalculator::calcHash(file);

    // MD5 от пустой строки
    EXPECT_EQ(hash, "d41d8cd98f00b204e9800998ecf8427e");
}

TEST(HashCalculatorTest, ConsistentHashing) {
    std::stringstream file1("test content");
    std::stringstream file2("test content"); // То же содержимое

    EXPECT_EQ(HashCalculator::calcHash(file1), HashCalculator::calcHash(file2));
}