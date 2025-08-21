#include <gtest/gtest.h>
#include "core/Logger.h"
#include <sstream>

class LoggerTest : public ::testing::Test {
protected:
    std::stringstream cout_buffer;
    std::stringstream cerr_buffer;
    std::streambuf* old_cout_buf;
    std::streambuf* old_cerr_buf;

    void SetUp() override {
        old_cout_buf = std::cout.rdbuf(cout_buffer.rdbuf());
        old_cerr_buf = std::cerr.rdbuf(cerr_buffer.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(old_cout_buf);
        std::cerr.rdbuf(old_cerr_buf);
    }
};

TEST_F(LoggerTest, LogsInfoMessages) {
    Core::Logger::log(Core::Logger::Level::Info, "This is an info message.");
    EXPECT_EQ(cout_buffer.str(), "[INFO] This is an info message.\n");
    EXPECT_TRUE(cerr_buffer.str().empty());
}

TEST_F(LoggerTest, LogsWarningMessages) {
    Core::Logger::log(Core::Logger::Level::Warning, "This is a warning message.");
    EXPECT_EQ(cerr_buffer.str(), "[WARNING] This is a warning message.\n");
    EXPECT_TRUE(cout_buffer.str().empty());
}

TEST_F(LoggerTest, LogsErrorMessages) {
    Core::Logger::log(Core::Logger::Level::Error, "This is an error message.");
    EXPECT_EQ(cerr_buffer.str(), "[ERROR] This is an error message.\n");
    EXPECT_TRUE(cout_buffer.str().empty());
}
