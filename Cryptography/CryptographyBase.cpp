#include "CryptographyBase.h"
#include <openssl/err.h>

std::string CryptographyBase::HandleError() const {
    char errBuffer[256];
    ERR_error_string(ERR_get_error(), errBuffer);
    std::string errMessage = errBuffer;
    return errMessage;
}
