#pragma once
#include "../DigestPOD.h"
#include "../../../Interfaces/IFileHandler.h"
#include "../../../Interfaces/ILogger.h"
#include "../../KdfDigester/IKdfDigester.h"

class DigesterService {
public:
    DigesterService(IKdfDigester &kdfDigester, ILogger &logger);

    /*std::pair<std::vector<unsigned char>, std::vector<unsigned char> > Digest(const std::string &password);*/
    DigestResult Digest(const std::string &password);

    bool VerifyDigest(
        const std::string &password,
        std::vector<unsigned char> &salt,
        std::vector<unsigned char> &key
    );

private:
    IKdfDigester &_kdfDigester;
    ILogger &_logger;
    int _saltLength = 16;
    int _keyLength = 32;
};