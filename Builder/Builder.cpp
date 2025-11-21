#include "Builder.h"
#include "../SimpleCrypt.h"

Builder::Builder(const int argc, char *argv[])
    : _fileHandler(),
      _logger(_fileHandler),
      _kdfDigester(8000),
      _digesterService(_kdfDigester, _logger),
      _encryptionService(_aesGcmCipher, _digesterService, _fileHandler, _logger),
      _decryptionService(_aesGcmCipher, _digesterService, _fileHandler, _logger),
      _cmd(_fileHandler, _logger, _encryptionService, _decryptionService),
      _argsHandler(_cmd),
      _argc(argc), _argv(argv) {
};

SimpleCrypt Builder::Build() {
    return {_argsHandler, _argc, _argv};
}
