#include "../HashingServices/DigesterService.h"

#include <openssl/rand.h>

DigesterService::DigesterService(IKdfDigester &kdfDigester, ILogger &logger)
    : _kdfDigester(kdfDigester), _logger(logger) {}

std::pair<std::vector<unsigned char>, std::vector<unsigned char>> DigesterService::Digest(const std::string &password) {
    _logger.log(LogLevel::INFO, "starting Hash and Salting method");

    std::vector<unsigned char> salt(16);
    /*unsigned int iter = 80000;*/
    std::vector<unsigned char> key(32);

    if(RAND_bytes(salt.data(), 16) != 1) {
        _logger.log(LogLevel::ERROR, "Failed to generate salt");
        return {{},{}};
    };

    /*auto result = kdf_passwd(password, salt, iter, key);*/
    auto result = _kdfDigester.DeriveKey(password, salt, key);

    if (!result) {
        _logger.log(LogLevel::ERROR, "Something went Wrong in hashAndSalt");
        return {{},{}};
    }
    return {salt, key};
}

bool DigesterService::VerifyDigest(
    const std::string &password,
    std::vector<unsigned char> &salt,
    std::vector<unsigned char> &key) {

    if (salt.empty()) {
        _logger.log(LogLevel::ERROR, "Salt is empty");
        return {};
    }

    _logger.log(LogLevel::INFO, "Verifying pwd");
    /*std::vector<unsigned char> salt(16);*/
    /*unsigned int iter = 80000;*/
    /*std::vector<unsigned char> key(32);*/

    /*salt = saltFromDoc;*/

    auto result = _kdfDigester.DeriveKey(password, salt, key);

    if (!result) {
        _logger.log(LogLevel::ERROR, "Something went Wrong in hashAndSalt");
        return {};
    }

    return true;
    /*return key;*/
}
