#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include "Report.h"

// ������ ��� ��������/�������
#ifdef SCANNER_LIBRARY_EXPORTS
#define SCANNER_API __declspec(dllexport)
#else
#define SCANNER_API __declspec(dllimport)
#endif
/**
 * @brief �������� ����� ����������-�������.
 *
 * ����� ������������� ����� ����� ��� ������� �������� ������������ �������� �������
 * �� ������� ����������� ������ � �������������� ���� ����� � ����������� �����������.
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
    * @brief ��������� ������� ������������ �������� �������.
    *
    * ����� �������������� ����������� ���������� (���� ������, ������, ������),
    * ��������� ����������� ������������ ��������� ���������� � ���������� ����� � ����������.
    *
    * @param base ���� � CSV-����� � ����� ����������� �����.
    * @param log  ���� � ����� ��� ������ �����.
    * @param path ���� � �������� ���������� ��� ������������.
    * @return Report ������ � ������������ ������������ (���������� ������, ������, ����� � �.�.).
    *
    * @note ������������ ������ Report �������� ��������������� � return-���������
    *       � ����������� RVO (Return Value Optimization) ��� ��������� ������� �����������.
    *
    * @throws std::runtime_error ���� �� ������� ������� ����� ���� ��� ����,
    *                            ��� ���� ��������� ���������� ����������.
    *
    */
	Report run(const std::string& base, const std::string& log, const std::string& path);
};


#endif // !APPLICATION_H
