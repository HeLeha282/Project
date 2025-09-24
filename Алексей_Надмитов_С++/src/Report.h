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
 * @brief ����� ��� ����� � ����������� ���������� ������������.
 *
 * ����� ������������� ���������������� ������ ��� ���������� ����������
 * � �������� ������������ ������ � ������ ��������� ������.
 * ��� �������� ����������� ��� ��������� ���������� ��� �����������
 * ������������� � ������������� �����.
 */
class SCANNER_API Report {
public:
    /**
     * @brief ����������� ������� ������������ ������ �� 1.
     */
    void addFileProcessed();

    /**
     * @brief ����������� ������� ���������� ������ �� 1.
     */
    void addInfected();

    /**
     * @brief ����������� ������� ������ ������ �� 1.
     */
    void addHealthy();

    /**
     * @brief ����������� ������� ������ �� 1.
     */
    void addError();

    /**
     * @brief ������������� ����� ���������� ������������.
     * @param[in] seconds ����� ���������� � ��������.
     */
    void setElapsedTime(double seconds);

    /**
     * @brief ������� �������� ����� ������������ � �������.
     *
     * ������ ������:
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
     * @brief ����������� �� ���������.
     * �������������� ��� �������� �������� ����������.
     */
    Report();

    /**
     * @brief ����������� �����������.
     * @param[in] other ������ Report ��� �����������.
     *
     * @note ����������� noexcept ��� ����������� ������������� � ����������� STL.
     */
    Report(Report&& other) noexcept;

    int getTotalFiles();
    int getInfectedFiles();
    int getHealthyFiles();
    int getErrors();
private:
    std::atomic<int> totalFiles{ 0 };     ///< ����� ���������� ������������ ������
    std::atomic<int> infectedFiles{ 0 };  ///< ���������� ������������ ���������� ������
    std::atomic<int> healthyFiles{ 0 };   ///< ���������� ������ ������
    std::atomic<int> errors{ 0 };         ///< ���������� ������ ��� ���������
    double elapsedTime = 0.0;             ///< ����� ���������� ������������ � ��������
};
#endif // !REPORT_H