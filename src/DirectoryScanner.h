#ifndef DIRECTORY_SCANNER_H
#define DIRECTORY_SCANNER_H
#include "Database.h"
#include "Logger.h"
#include "Report.h"
#include <string>
#include "fileHandler.h"
/**
 * @brief ����� ��� ������������ ������������ ���������� � �������� ������.
 *
 * ������������ ������������� ������������ �������� �������, �������� ����� �� �������
 * � ���� ����������� �����. ��� ������� ����� ��������� FileHandler � ��������� ������.
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
     * @brief ����������� �������.
     *
     * @param base   ������ �� ���� ������ ����������� �����.
     * @param logger ������ �� ������ ��� ������ �������.
     * @param report ������ �� ����� ��� ����� ����������.
     */
    DirectoryScanner(Database& base, Logger& logger, Report& report);

    /**
     * @brief ��������� ����������� ������������ ��������� ����������.
     *
     * ��������� ����������� ����������, ����� ��������� ������������� ������������
     * ���� ��������� ������ � �����.
     *
     * @param path ���� � �������� ���������� ��� ������������.
     *
     * @throws std::runtime_error ���� ���������� �� ����������, ����������
     *                            ��� ��������� ������ �� ����� ������������.
     *
     * @note ������ ������� � ��������� ������/������ ����������, �� �� ��������� ������������.
     */
    void scan(std::string path);

private:
    Database& database;    ///< ������ �� ���� ����������� �����
    Logger& logger;        ///< ������ �� ������
    Report& report;        ///< ������ �� ����� �� �����������

    /**
     * @brief ��������� ����������� ���������� ��� ������.
     *
     * @param dir ���� � ����������� ����������.
     * @return true ���� ���������� �������� ��� ������.
     * @return false ���� ������ � ���������� ��������.
     */
    bool canAccessDirectory(const std::filesystem::path& dir);

    /**
     * @brief ���������� ��������� ���������� � ������������ ����� � ������������� ������.
     *
     * ���������� ��� ������� � ������������ ���������� ������������ ���������� �������.
     * ��� ������� ����� ��������� ��������� ����� ���������.
     *
     * @param directory ���� � ����������� ����������.
     *
     * @note ������������ ���������� ������������� ������� ���������� ����������� ���������� �������.
     */
    void scanDirectory(const std::filesystem::path& directory);
};

#endif // !DIRECTORY_SCANNER_H