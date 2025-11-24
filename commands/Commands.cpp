#include "Commands.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include "../FileHandling/FileHandler.h"
#include "../POD/UserInput.h"
#include "../Data/UI/UiText.h"
#include "../Render/RenderCmd.h"


Commands::Commands(
    IFileHandler &fileHandlerInstance,
    ILogger &loggerInstance,
    EncryptionService &encryptionService,
    DecryptionService &decryptionService)
    : _fileHandler(fileHandlerInstance),
      _logger(loggerInstance),
      _encryptionService(encryptionService),
      _decryptionService(decryptionService) {
    commands[CRYPT] = [this](const userInput &userInput) { encrypt(userInput); };
    commands[DECRYPT] = [this](const userInput &userInput) { decrypt(userInput); };
    commands[COMPRESS] = [this](const userInput &userInput) { compress(userInput); };
}

/*
 *   TODO
 *      Go through file and count occurrence of word or char;
 *      save to map e.g (word -> occurrence);
 *      use huffman tree on map;
 *      use bit codes from huffman tree to remap the words with the bit codes;
 *      save a "dictionary" of the code -> word for decompression;
 */
void Commands::compress(const userInput &file) {
    RenderCmd::WriteOut("testing compress method of commands\n");
    auto occurrences = CountCharOccurrences(file.filename);
    int n = 0;
    for (const auto &[key, value]: occurrences) {
        std::cout << n << " Key " << key << " occurrence " << value << std::endl;
        n++;
    }
}

std::unordered_map<unsigned char, int> Commands::CountCharOccurrences(const std::string &filename) {
    const auto filedata = _fileHandler.readFromFile(filename);

    std::unordered_map<unsigned char, int> occurrences;
    for (const auto &data: filedata) {
        if (data != '\r') occurrences[data]++;
    }
    return occurrences;
}

void Commands::encrypt(const userInput &userInput) {
    _encryptionService.EncryptFile(userInput.filename, userInput.password);
}

void Commands::decrypt(const userInput &userInput) {
    _decryptionService.DecryptFile(userInput.filename, userInput.password);
}


/*void Commands::HandleError() const {
char errBuffer[256];
ERR_error_string(ERR_get_error(), errBuffer);
_logger.log(LogLevel::ERROR, errBuffer);
}

void Commands::HandleError(EVP_CIPHER_CTX *ctx) const {
HandleError();
if (ctx) EVP_CIPHER_CTX_free(ctx);
}

void Commands::HandleError(EVP_MD_CTX *mctx) const {
HandleError();
if (mctx) EVP_MD_CTX_free(mctx);
}
void Commands::HandleError(EVP_KDF *kdf, EVP_KDF_CTX *kctx, OSSL_LIB_CTX *lib_ctx) const {
HandleError();
if (kctx) EVP_KDF_CTX_free(kctx);
if (kdf) EVP_KDF_free(kdf);
if (lib_ctx) OSSL_LIB_CTX_free(lib_ctx);
}*/
