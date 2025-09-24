#include <gtest/gtest.h>
#include "Database.h"
#include <filesystem>
#include <fstream>

class DatabaseTest : public ::testing::Test {
protected:
    void SetUp() override {
        // גנולוםûי CSV פאיכ הכÿ עועמג
        std::ofstream file("test_hashes.csv");
        file << "hash1;Virus1\n";
        file << "hash2;Virus2\n";
        file.close();
    }

    void TearDown() override {
        std::filesystem::remove("test_hashes.csv");
    }
};

TEST_F(DatabaseTest, LoadsHashesFromFile) {
    Database db("test_hashes.csv");
    EXPECT_EQ(db.getVerdict("hash1"), "Virus1");
    EXPECT_EQ(db.getVerdict("hash2"), "Virus2");
}

TEST_F(DatabaseTest, ReturnsEmptyForUnknownHash) {
    Database db("test_hashes.csv");
    EXPECT_EQ(db.getVerdict("unknown_hash"), "");
}

TEST_F(DatabaseTest, ThrowsOnMissingFile) {
    EXPECT_THROW(Database db("nonexistent.csv"), std::runtime_error);
}