#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include "Report.h"

// Макрос для экспорта/импорта
#ifdef SCANNER_LIBRARY_EXPORTS
#define SCANNER_API __declspec(dllexport)
#else
#define SCANNER_API __declspec(dllimport)
#endif
/**
 * @brief Основной класс приложения-сканера.
 *
 * Класс предоставляет точку входа для запуска процесса сканирования файловой системы
 * на наличие вредоносных файлов с использованием базы хэшей и логирования результатов.
 *
 * @class Application
 * @see Database
 * @see Logger
 * @see DirectoryScanner
 * @see Report
 */
class SCANNER_API Application {
public:
    /**
    * @brief Запускает процесс сканирования файловой системы.
    *
    * Метод инициализирует необходимые компоненты (базу данных, логгер, сканер),
    * запускает рекурсивное сканирование указанной директории и возвращает отчёт о выполнении.
    *
    * @param base Путь к CSV-файлу с базой вредоносных хэшей.
    * @param log  Путь к файлу для записи логов.
    * @param path Путь к корневой директории для сканирования.
    * @return Report Объект с результатами сканирования (количество файлов, ошибок, время и т.д.).
    *
    * @note Возвращаемый объект Report создаётся непосредственно в return-выражении
    *       с применением RVO (Return Value Optimization) для избежания лишнего копирования.
    *
    * @throws std::runtime_error Если не удалось открыть файлы базы или лога,
    *                            или если указанная директория недоступна.
    *
    */
	Report run(const std::string& base, const std::string& log, const std::string& path);
};


#endif // !APPLICATION_H
