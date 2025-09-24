#ifndef REPORT_H
#define REPORT_H

#ifdef SCANNER_LIBRARY_EXPORTS
#define SCANNER_API __declspec(dllexport)
#else
#define SCANNER_API __declspec(dllimport)
#endif
#include <atomic>

/**
 * @class Report
 * @brief Класс для сбора и отображения статистики сканирования.
 *
 * Класс предоставляет потокобезопасные методы для накопления статистики
 * в процессе сканирования файлов и вывода итогового отчета.
 * Все счетчики реализованы как атомарные переменные для безопасного
 * использования в многопоточной среде.
 */
class SCANNER_API Report {
public:
    /**
     * @brief Увеличивает счетчик обработанных файлов на 1.
     */
    void addFileProcessed();

    /**
     * @brief Увеличивает счетчик зараженных файлов на 1.
     */
    void addInfected();

    /**
     * @brief Увеличивает счетчик чистых файлов на 1.
     */
    void addHealthy();

    /**
     * @brief Увеличивает счетчик ошибок на 1.
     */
    void addError();

    /**
     * @brief Устанавливает время выполнения сканирования.
     * @param[in] seconds Время выполнения в секундах.
     */
    void setElapsedTime(double seconds);

    /**
     * @brief Выводит итоговый отчет сканирования в консоль.
     *
     * Формат вывода:
     * \code
     * ===== SCAN REPORT =====
     * Total files processed: 150
     * Infected files found: 3
     * Healthy files found: 147
     * Errors encountered: 2
     * Time elapsed: 12.34 seconds
     * \endcode
     */
    void printReport();

    /**
     * @brief Конструктор по умолчанию.
     * Инициализирует все счетчики нулевыми значениями.
     */
    Report();

    /**
     * @brief Конструктор перемещения.
     * @param[in] other Объект Report для перемещения.
     *
     * @note Гарантирует noexcept для безопасного использования в контейнерах STL.
     */
    Report(Report&& other) noexcept;

    int getTotalFiles();
    int getInfectedFiles();
    int getHealthyFiles();
    int getErrors();
private:
    std::atomic<int> totalFiles{ 0 };     ///< Общее количество обработанных файлов
    std::atomic<int> infectedFiles{ 0 };  ///< Количество обнаруженных зараженных файлов
    std::atomic<int> healthyFiles{ 0 };   ///< Количество чистых файлов
    std::atomic<int> errors{ 0 };         ///< Количество ошибок при обработке
    double elapsedTime = 0.0;             ///< Время выполнения сканирования в секундах
};
#endif // !REPORT_H