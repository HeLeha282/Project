#include <gtest/gtest.h>
#include "HashCalculator.h"
#include <fstream>
#include <filesystem> 
#include <cstdio>    


class HashCalculatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        
    }

    void TearDown() override {
        // удаление временных файлы после каждого теста
        if (std::filesystem::exists(testFilePath)) {
            std::remove(testFilePath.c_str());
        }
    }

    // для создания файла с содержимым
    void createTestFile(const std::string& content) {
        std::ofstream file(testFilePath);
        file << content;
        file.close();
    }

    const std::string testFilePath = "test_temp_file.txt";
};


TEST_F(HashCalculatorTest, CalculatesCorrectMD5) {
    createTestFile("hello world");

    std::ifstream file(testFilePath);
    std::string hash = HashCalculator::calcHash(file);

    EXPECT_EQ(hash, "5eb63bbbe01eeed093cb22bb8f5acdc3");
}

TEST_F(HashCalculatorTest, HandlesEmptyFile) {
    createTestFile(""); 

    std::ifstream file(testFilePath);
    std::string hash = HashCalculator::calcHash(file);

    EXPECT_EQ(hash, "d41d8cd98f00b204e9800998ecf8427e");
}

TEST_F(HashCalculatorTest, ConsistentHashing) {
    const std::string content = "test content";

    // првый файл
    createTestFile(content);
    std::ifstream file1(testFilePath);
    std::string hash1 = HashCalculator::calcHash(file1);

    // еще файд с тем же содержимым
    createTestFile(content); // перезапись файла
    std::ifstream file2(testFilePath);
    std::string hash2 = HashCalculator::calcHash(file2);

    EXPECT_EQ(hash1, hash2);
}

