add_executable(SimpleCryptographTests test.cpp
        ../Interfaces/IFileHandler.h
        ../FileHandling/FileHandler.cpp
          ../FileHandling/FileHandler.h
          ../Render/RenderCmd.cpp
          ../Render/RenderCmd.h
          TestMocks.h
          ../Logger/Logger.cpp
          ../Logger/Logger.h
          ../Interfaces/IFileHandler.h
          ../Interfaces/ILogger.h
          ../commands/CommandTypes.h
          ../commands/Commands.cpp
          ../commands/Commands.h
          ../Cryptography/AesGcmEncryptor/AesGcmCipher.cpp
          ../Cryptography/AesGcmEncryptor/AesGcmCipher.h
          ../Cryptography/AesGcmEncryptor/IEncrypt.h
          ../Cryptography/CryptographyServices/EncryptionService/EncryptionService.cpp
          ../Cryptography/CryptographyServices/EncryptionService/EncryptionService.h
          ../Cryptography/KdfDigester/KdfDigester.cpp
          ../Cryptography/KdfDigester/KdfDigester.h
          ../Cryptography/KdfDigester/IKdfDigester.h
          ../Cryptography/CryptographyServices/HashingService/DigesterService.cpp
          ../Cryptography/CryptographyServices/HashingService/DigesterService.h
          ../Cryptography/CryptographyServices/DecryptionService/DecryptionService.cpp
          ../Cryptography/CryptographyServices/DecryptionService/DecryptionService.h
        ../Cryptography/CryptoStatus.h
        ../Cryptography/CryptographyBase.cpp
        ../Cryptography/CryptographyBase.h
)

target_link_libraries(SimpleCryptographTests PRIVATE
        Catch2::Catch2WithMain
        OpenSSL::SSL
        OpenSSL::Crypto
)

include(CTest)
include(Catch)
catch_discover_tests(SimpleCryptographTests)