#include "StringUtils.h"

std::string StringUtils::trim(const std::string& str)
{
    const std::string whitespace = " \t\n\r\f\v";

    // Находим первый непробельный символ
    size_t start = str.find_first_not_of(whitespace);
    if (start == std::string::npos) return ""; // Вся строка - пробелы

    // Находим последний непробельный символ
    size_t end = str.find_last_not_of(whitespace);

    return str.substr(start, end - start + 1);
}
