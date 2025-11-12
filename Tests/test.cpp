#include <fstream>
#include <catch2/catch_test_macros.hpp>

#include "TestMocks.h"
#include "../ArgumentHandler/ArgsHandler.h"
#include "../commands/Commands.h"
#include "../FileHandling/FileHandler.h"
#include "../Logger/Logger.h"
#include "../Data/UI/UiText.h"
#include "../Data/UI/ErrorText.h"

TEST_CASE("File Handler", "[file]") {
    FileHandler fileHandler;
    SECTION("Read File") {
        /*FileHandler fileHandler;*/

        const auto data = fileHandler.readFromFile("testData.txt");

        REQUIRE_FALSE(data.empty());
    }
    SECTION("Write File") {
        /*FileHandler fileHandler;*/
         fileHandler.writeToFile("TestingWriteMethod.txt", "Data being written by test");

        CHECK_NOTHROW(fileHandler.writeToFile("Data being written by test",
            "TestingWriteMethod.txt"));
    }

    SECTION("file exist") {
        CHECK(fileHandler.fileExists("testData.txt"));
        CHECK_FALSE(fileHandler.fileExists("ii.txt"));
    }
}


TEST_CASE("Logger") {
    MockFileHandler mockFileHandler;
    Logger logger(mockFileHandler);

    SECTION("GetCurrentFormatedTime()") {
        logger.log(LogLevel::INFO, "test message");

        REQUIRE(mockFileHandler.writtenFile == "LogData/Log.txt");
        REQUIRE(mockFileHandler.writtenData.find("test message") != std::string::npos);
        REQUIRE(mockFileHandler.writtenData.find("INFO") != std::string::npos);
        REQUIRE(mockFileHandler.writtenData.front() == '[');

    }
}