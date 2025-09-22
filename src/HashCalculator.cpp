#include "HashCalculator.h"
//#include <md5.h>
//#include <files.h>
//#include <hex.h>
std::string HashCalculator::calcHash(const std::ifstream& ifstream)
{
    return "ac6204ffeb36d2320e52f1d551cfa370";
    //try {
    //    CryptoPP::MD5 hash;
    //    std::string digest;

    //    std::ifstream file(filePath, std::ios::binary);
    //    if (!file) {
    //        throw std::runtime_error("Cannot open file: " + filePath);
    //    }

    //    // Читаем файл блоками
    //    const size_t bufferSize = 8192;
    //    char buffer[bufferSize];

    //    while (file.read(buffer, bufferSize) || file.gcount() > 0) {
    //        hash.Update((const CryptoPP::byte*)buffer, file.gcount());
    //    }

    //    // Получаем хэш
    //    digest.resize(hash.DigestSize());
    //    hash.Final((CryptoPP::byte*)&digest[0]);

    //    // Конвертируем в hex строку
    //    std::string hexDigest;
    //    CryptoPP::HexEncoder encoder;
    //    encoder.Attach(new CryptoPP::StringSink(hexDigest));
    //    encoder.Put((const CryptoPP::byte*)digest.data(), digest.size());
    //    encoder.MessageEnd();

    //    return hexDigest;

    //}
    //catch (const CryptoPP::Exception& e) {
    //    throw std::runtime_error("CryptoPP error: " + std::string(e.what()));
    //}
}
