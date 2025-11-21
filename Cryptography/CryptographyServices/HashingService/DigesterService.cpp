#include "../HashingService/DigesterService.h"

#include <openssl/rand.h>

#include "../DigestPOD.h"

DigesterService::DigesterService(IKdfDigester &kdfDigester, ILogger &logger)
    : _kdfDigester(kdfDigester), _logger(logger) {
}


/*TODO set a better error handling then returning empty*/
DigestResult DigesterService::Digest(const std::string &password) {
    _logger.log(LogLevel::INFO, "starting Hash and Salting method");

    std::vector<unsigned char> salt(_saltLength);
    std::vector<unsigned char> key(_keyLength);

    if (RAND_bytes(salt.data(), _saltLength) != 1) {
        _logger.log(LogLevel::ERROR, "Failed to generate salt");
        return {{}, {}};
    };

    const auto result = _kdfDigester.DeriveKey(password, salt, key);

    if (!result) {
        _logger.log(LogLevel::ERROR, "Something went Wrong in hashAndSalt");
        return {{}, {}};
    }

    return DigestResult{
        .key = key,
        .salt = salt
    };
}

bool DigesterService::VerifyDigest(
    const std::string &password,
    std::vector<unsigned char> &salt,
    std::vector<unsigned char> &key
) {
    if (salt.empty()) {
        _logger.log(LogLevel::ERROR, "Salt is empty");
        return {};
    }

    _logger.log(LogLevel::INFO, "Verifying pwd");

    const auto result = _kdfDigester.DeriveKey(password, salt, key);

    if (!result) {
        _logger.log(LogLevel::ERROR, "Something went Wrong in hashAndSalt");
        return {};
    }

    return true;
}
