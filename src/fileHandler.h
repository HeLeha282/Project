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
 * @brief ����� ��� ��������� ��������� ������.
 *
 * �������� �� ���������� ���� �����, �������� ��� � ���� ����������� �����
 * � ���������� ���������� � ������. ������ ��������� ������������ ��� ��������� ������ �����.
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
     * @brief ����������� ����������� ������.
     *
     * @param base   ������ �� ���� ������ ����������� �����.
     * @param logger ������ �� ������ ��� ������ �������.
     * @param report ������ �� ����� ��� ����� ����������.
     */
    FileHandler(Database& base, Logger& logger, Report& report);

    /**
     * @brief ������������ ���� ����: ��������� ��� � ��������� �� �������������.
     *
     * ����� ��������� ���������������:
     * 1. ����������� ������� ������������ ������
     * 2. ��������� ���� � �������� ������
     * 3. ��������� MD5-��� �����������
     * 4. ��������� ��� � ���� ������
     * 5. ��������� ���������� � �������� ���������
     *
     * @param filePath ������ ���� � ��������������� �����.
     *
     * @note ��� ������ �������� ����� ������������� ������� ������ � ������ ����������� � ���.
     * @note ����� �������� ������� �������������� �������� ��� �������� � ������ �������.
     */
    void processFile(const std::string& filePath);

private:
    Database& database;    ///< ������ �� ���� ����������� �����
    Logger& logger;        ///< ������ �� ������ ��� ������ �������
    Report& report;        ///< ������ �� ����� ��� ����� ����������
};
#endif // !FILE_HANDLER_H