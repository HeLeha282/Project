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
 * @brief ������������ ����, ���������� ���������� ������ HashCalculator.
 */

 /**
  * @class HashCalculator
  * @brief �����, ��������������� ����������� ����� ��� ���������� MD5-���� �����.
  *
  * ����� �������� ������������ ����������� �����, ������� ��������� ���-����� MD5
  * ��� ����������� ����������� ��������� ������. �������� � ������� ������ �������,
  * ����� ������ �������.
  */
class SCANNER_API HashCalculator {
public:
    /**
     * @brief ��������� MD5-��� ����������� �����.
     *
     * ����� ������ ���� ������� �� 4 ��, ��� ��������� ������������ �����,
     * ������ ������� ��������� ��������� ����� ����������� ������.
     *
     * @param[in] file �������� �������� ����� � �������� ������ ��� ������.
     * @return std::string ������ � hex-�������������� MD5-���� (32 ������� � ������ ��������).
     *
     * @throws std::runtime_error ���� �� ����� ������ ����� ��������� ������ (���� ���������� ��� ���������).
     *
     * @note ���� ������ ���� ������ � �������� ������ ����� ��������� � �����.
     * @note ����� ���������� ���� ������� ������ � ����� ����� ��������.
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