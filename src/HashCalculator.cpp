#include "HashCalculator.h"
#include <openssl/md5.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

std::string HashCalculator::calcHash(std::ifstream& file) {
    unsigned char c[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext;

    MD5_Init(&mdContext);

    // Читаем файл блоками по 4KB
    const size_t bufferSize = 4096;
    char buffer[bufferSize];

    while (file.good()) {
        file.read(buffer, bufferSize);
        MD5_Update(&mdContext, buffer, file.gcount());
    }

    MD5_Final(c, &mdContext);

    // Переводим байты в hex-строку
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        oss << std::setw(2) << static_cast<int>(c[i]);
    }

    if (file.bad()) {//надо будет доработать
        throw std::runtime_error("Ошибка чтения файла при вычислении хеша");
    }

    return oss.str();
}