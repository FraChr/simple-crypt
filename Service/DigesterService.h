#pragma once
#include "../Interfaces/IFileHandler.h"
#include "../Interfaces/ILogger.h"
#include "../KdfDigester/IKdfDigester.h"

class DigesterService {
public:
    DigesterService(IKdfDigester &kdfDigester, ILogger &logger);
    std::pair<std::vector<unsigned char>, std::vector<unsigned char>> Digest(std::string &password);

    bool VerifyDigest(
        std::string &password,
        std::vector<unsigned char> &salt,
        std::vector<unsigned char> &key
        );


private:
    IKdfDigester &_kdfDigester;
    ILogger &_logger;
};
