#ifndef DIRECTORY_SCANNER_H
#define DIRECTORY_SCANNER_H
#include "Database.h"
#include "Logger.h"
#include "Report.h"
#include <string>
#include "fileHandler.h"
/**
 * @brief Класс для рекурсивного сканирования директорий и проверки файлов.
 *
 * Осуществляет многопоточное сканирование файловой системы, проверяя файлы на наличие
 * в базе вредоносных хэшей. Для каждого файла создается FileHandler в отдельном потоке.
 *
 * @class DirectoryScanner
 * @see Database
 * @see Logger
 * @see Report
 * @see FileHandler
 */
class DirectoryScanner {
public:
    /**
     * @brief Конструктор сканера.
     *
     * @param base   Ссылка на базу данных вредоносных хэшей.
     * @param logger Ссылка на логгер для записи событий.
     * @param report Ссылка на отчет для сбора статистики.
     */
    DirectoryScanner(Database& base, Logger& logger, Report& report);

    /**
     * @brief Запускает рекурсивное сканирование указанной директории.
     *
     * Проверяет доступность директории, затем запускает многопоточное сканирование
     * всех вложенных файлов и папок.
     *
     * @param path Путь к корневой директории для сканирования.
     *
     * @throws std::runtime_error Если директория не существует, недоступна
     *                            или произошла ошибка во время сканирования.
     *
     * @note Ошибки доступа к отдельным файлам/папкам логируются, но не прерывают сканирование.
     */
    void scan(std::string path);

private:
    Database& database;    ///< Ссылка на базу вредоносных хэшей
    Logger& logger;        ///< Ссылка на логгер
    Report& report;        ///< Ссылка на отчет со статистикой

    /**
     * @brief Проверяет доступность директории для чтения.
     *
     * @param dir Путь к проверяемой директории.
     * @return true Если директория доступна для чтения.
     * @return false Если доступ к директории запрещен.
     */
    bool canAccessDirectory(const std::filesystem::path& dir);

    /**
     * @brief Рекурсивно сканирует директорию и обрабатывает файлы в многопоточном режиме.
     *
     * Использует пул потоков с ограничением количества одновременно работающих потоков.
     * Для каждого файла создается отдельный поток обработки.
     *
     * @param directory Путь к сканируемой директории.
     *
     * @note Максимальное количество одновременных потоков ограничено количеством аппаратных потоков.
     */
    void scanDirectory(const std::filesystem::path& directory);
};

#endif // !DIRECTORY_SCANNER_H