#ifndef HASH_CALCULATOR_H
#define HASH_CALCULATOR_H
#include <string>

#ifdef SCANNER_LIBRARY_EXPORTS
#define SCANNER_API __declspec(dllexport)
#else
#define SCANNER_API __declspec(dllimport)
#endif
/**
 * @file HashCalculator.h
 * @brief Заголовочный файл, содержащий объявление класса HashCalculator.
 */

 /**
  * @class HashCalculator
  * @brief Класс, предоставляющий статический метод для вычисления MD5-хеша файла.
  *
  * Класс содержит единственный статический метод, который вычисляет хеш-сумму MD5
  * для содержимого переданного файлового потока. Работает с файлами любого размера,
  * читая данные блоками.
  */
class SCANNER_API HashCalculator {
public:
    /**
     * @brief Вычисляет MD5-хеш содержимого файла.
     *
     * Метод читает файл блоками по 4 КБ, что позволяет обрабатывать файлы,
     * размер которых превышает доступный объем оперативной памяти.
     *
     * @param[in] file Открытый файловый поток в бинарном режиме для чтения.
     * @return std::string Строка с hex-представлением MD5-хеша (32 символа в нижнем регистре).
     *
     * @throws std::runtime_error Если во время чтения файла произошла ошибка (файл недоступен или поврежден).
     *
     * @note Файл должен быть открыт в бинарном режиме перед передачей в метод.
     * @note После вычисления хеша позиция чтения в файле будет изменена.
     *
     * @example
     * @code
     * std::ifstream file("example.txt", std::ios::binary);
     * if (file.is_open()) {
     *     std::string hash = HashCalculator::calcHash(file);
     *     std::cout << "MD5: " << hash << std::endl;
     * }
     * @endcode
     */
    static std::string calcHash(std::ifstream& file);
};

#endif // !HASH_CALCULATOR_H