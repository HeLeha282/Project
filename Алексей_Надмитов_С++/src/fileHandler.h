#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include "Database.h"
#include "Logger.h"
#include "Report.h"
#include <string>

#ifdef SCANNER_LIBRARY_EXPORTS
#define SCANNER_API __declspec(dllexport)
#else
#define SCANNER_API __declspec(dllimport)
#endif
/**
 * @brief Класс для обработки отдельных файлов.
 *
 * Отвечает за вычисление хэша файла, проверку его в базе вредоносных хэшей
 * и обновление статистики в отчете. Каждый экземпляр используется для обработки одного файла.
 *
 * @class FileHandler
 * @see Database
 * @see Logger
 * @see Report
 * @see HashCalculator
 */
class SCANNER_API FileHandler {
public:
    /**
     * @brief Конструктор обработчика файлов.
     *
     * @param base   Ссылка на базу данных вредоносных хэшей.
     * @param logger Ссылка на логгер для записи событий.
     * @param report Ссылка на отчет для сбора статистики.
     */
    FileHandler(Database& base, Logger& logger, Report& report);

    /**
     * @brief Обрабатывает один файл: вычисляет хэш и проверяет на вредоносность.
     *
     * Метод выполняет последовательно:
     * 1. Увеличивает счетчик обработанных файлов
     * 2. Открывает файл в бинарном режиме
     * 3. Вычисляет MD5-хэш содержимого
     * 4. Проверяет хэш в базе данных
     * 5. Обновляет статистику и логирует результат
     *
     * @param filePath Полный путь к обрабатываемому файлу.
     *
     * @note При ошибке открытия файла увеличивается счетчик ошибок и запись добавляется в лог.
     * @note Файлы большого размера обрабатываются потоково без загрузки в память целиком.
     */
    void processFile(const std::string& filePath);

private:
    Database& database;    ///< Ссылка на базу вредоносных хэшей
    Logger& logger;        ///< Ссылка на логгер для записи событий
    Report& report;        ///< Ссылка на отчет для сбора статистики
};
#endif // !FILE_HANDLER_H