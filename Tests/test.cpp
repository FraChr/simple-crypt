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

/*TEST_CASE("Passwords") {
    /*Commands m_commands(MockFileHandler, MockLogger);#1#
    std::vector<unsigned char> generatedSalt;
    SECTION("Password hashing/salt") {
        MockFileHandler mockFileHandler;
        MockLogger mockLogger;
        Commands command(mockFileHandler, mockLogger);


        std::string psw = "test";
        std::vector<unsigned char> salt(16);
        unsigned int iter = 80000;
        std::vector<unsigned char> key(32);


        RAND_bytes(salt.data(), salt.size());

        auto result = command.kdf_passwd(psw, salt, iter, key);

        generatedSalt = salt;

        if (!result) {
            std::cout << "ERROR no result is false\n";
        }

        for (const auto &c: salt) {
            std::cout << c;
        }
        for (const auto &c: generatedSalt) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    SECTION("verify password") {
        MockFileHandler mockFileHandler;
        MockLogger mockLogger;
        Commands command(mockFileHandler, mockLogger);

        std::string psw = "test";
        std::vector<unsigned char> salt(16);
        unsigned int iter = 80000;
        std::vector<unsigned char> key(32);

        salt = generatedSalt;

        auto result = command.kdf_passwd(psw, salt, iter, key);

        if (!result) {
            std::cout << "ERROR no result is false\n";
            return;
        }

        if (salt == generatedSalt) {
            std::cout << "Salt and generatedSalt is equal";
        } else {
            std::cout << "Salt and generatedSalt is not equal";
        }
    }
}*/

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
