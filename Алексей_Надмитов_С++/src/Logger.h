#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <fstream>
#include <chrono>
#include <mutex>
#ifdef SCANNER_LIBRARY_EXPORTS
#define SCANNER_API __declspec(dllexport)
#else
#define SCANNER_API __declspec(dllimport)
#endif
/**
 * @class Logger
 * @brief Класс для потокобезопасного логирования в файл.
 *
 * Класс предоставляет методы для записи различных типов сообщений в лог-файл:
 * - Обнаружение вредоносных файлов
 * - Ошибки при работе утилиты
 * - Информационные сообщения
 *
 * Все операции записи защищены мьютексом для корректной работы в многопоточной среде.
 * Формат записи: [ТИП] ВРЕМЯ | Дополнительная информация
 */
class SCANNER_API Logger {
private:
    std::ofstream log_file;       ///< Файловый поток для записи логов
    std::mutex log_mutex;         ///< Мьютекс для обеспечения потокобезопасности

public:
    /**
     * @brief Конструктор класса Logger.
     * @param[in] filename Путь к файлу для записи логов.
     * @throws std::runtime_error Если не удалось открыть файл для записи.
     */
    Logger(const std::string& filename);

    /**
     * @brief Записывает в лог информацию об обнаружении вредоносного файла.
     * @param[in] file_path Путь к обнаруженному файлу.
     * @param[in] hash MD5-хеш содержимого файла.
     * @param[in] verdict Вердикт (тип угрозы) для данного хеша.
     * @throws std::ios_base::failure При ошибке записи в файл.
     *
     * @example
     * Формат записи:
     * [DETECTED] 2024-01-15 14:30:25 | File: C:\path\to\file.exe | Hash: a9963513d093ffb2bc7ceb9807771ad4 | Verdict: Exploit
     */
    void logDetection(const std::string& file_path, const std::string& hash,
        const std::string& verdict);

    /**
     * @brief Записывает в лог сообщение об ошибке.
     * @param[in] error Текст ошибки.
     * @throws std::ios_base::failure При ошибке записи в файл.
     *
     * @example
     * Формат записи:
     * [ERROR] 2024-01-15 14:30:25 | Error: No permission to read file: C:\protected\file.exe
     */
    void logError(const std::string& error);

    /**
     * @brief Записывает в лог информационное сообщение.
     * @param[in] message Текст информационного сообщения.
     * @throws std::ios_base::failure При ошибке записи в файл.
     *
     * @example
     * Формат записи:
     * [INFO] 2024-01-15 14:30:25 | Scan started: path="C:\target_folder" base="malware_db.csv"
     * [INFO] 2024-01-15 14:30:25 | Threads: 4 | Recursive: true
     */
    void logInfo(const std::string& message);

    /**
     * @brief Деструктор класса Logger.
     * @note Автоматически закрывает файловый поток, если он открыт.
     */
    ~Logger();
};
#endif // !LOGGER_H