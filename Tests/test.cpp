#include <fstream>
#include <catch2/catch_test_macros.hpp>
#include <openssl/rand.h>

#include "TestMocks.h"
#include "../Cryptography/AesGcmEncryptor/AesGcmCipher.h"
#include "../commands/Commands.h"
#include "../FileHandling/FileHandler.h"
#include "../Cryptography/KdfDigester/KdfDigester.h"
#include "../Logger/Logger.h"
#include "../Cryptography/CryptographyServices/DecryptionService/DecryptionService.h"
#include "../Cryptography/CryptographyServices/EncryptionService/EncryptionService.h"


TEST_CASE("File Handler", "[file]") {
    FileHandler fileHandler;
    SECTION("Read File") {
        const auto data = fileHandler.readFromFile("../testData.txt");

        REQUIRE_FALSE(data.empty());
    }
    SECTION("Write File") {
        /*FileHandler fileHandler;*/
        fileHandler.writeToFile("../TestingWriteMethod.txt", "Data being written by test");

        CHECK_NOTHROW(fileHandler.writeToFile("Data being written by test",
            "TestingWriteMethod.txt"));
    }

    SECTION("file exist") {
        CHECK(fileHandler.fileExists("../testData.txt"));
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


TEST_CASE("Refactored Encryption") {
    /*MockFileHandler mockFileHandler;*/
    FileHandler fileHandler;
    MockLogger mockLogger;
    KdfDigester kdf_digester(8000);
    AesGcmCipher aes_gcm_encryptor;
    DigesterService digester_service(kdf_digester, mockLogger);
    EncryptionService encryption_service(aes_gcm_encryptor, digester_service, fileHandler, mockLogger);
    DecryptionService decryptionService(aes_gcm_encryptor, digester_service, fileHandler, mockLogger);
    MockUserInput mockUserInput;

    SECTION("Encryption") {
        const auto result = encryption_service.EncryptFile(mockUserInput.filename, mockUserInput.password);

        REQUIRE(result == true);
    }

    SECTION("Decryption") {
        const auto result = decryptionService.DecryptFile(mockUserInput.filename, mockUserInput.password);

        REQUIRE(result == true);
    }
}
