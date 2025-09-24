#ifndef DATABASE_H
#define DATABASE_H
#include <unordered_map>
#include <string>
#ifdef SCANNER_LIBRARY_EXPORTS
#define SCANNER_API __declspec(dllexport)
#else
#define SCANNER_API __declspec(dllimport)
#endif
/**
 * @brief Класс для работы с базой вредоносных хэшей.
 *
 * Загружает хэши и соответствующие им вердикты из CSV-файла и предоставляет
 * интерфейс для проверки хэшей на наличие в базе.
 *
 * @class Database
 */
class SCANNER_API Database {
public:
    /**
     * @brief Конструктор, загружающий базу из CSV-файла.
     *
     * @param csvFilePath Путь к CSV-файлу с хэшами и вердиктами.
     *
     * @throws std::runtime_error Если файл не существует, недоступен для чтения
     *                            или имеет некорректный формат.
     *
     * @see load()
     */
    Database(const std::string& csvFilePath);

    /**
     * @brief Проверяет, содержится ли хэш в базе вредоносных.
     *
     * @param hash MD5-хэш файла в виде строки (в нижнем регистре, без разделителей).
     * @return std::string Вердикт из базы, если хэш найден; иначе — пустая строка.
     *
     */
    std::string getVerdict(std::string hash);

private:
    /**
     * @brief Загружает данные из CSV-файла в память.
     *
     * Формат CSV: каждая строка содержит хэш и вердикт, разделенные символом ';'.
     * Пустые строки пропускаются. Пробельные символы вокруг хэша и вердикта обрезаются.
     *
     * @param csvFilePath Путь к CSV-файлу.
     *
     * @throws std::runtime_error При ошибках чтения или парсинга файла.
     *
     * @see StringUtils::trim()
     */
    void load(const std::string& csvFilePath);

    std::unordered_map<std::string, std::string> maliciousHashes; ///< Хранилище хэшей и вердиктов
};

#endif // !DATABASE_H