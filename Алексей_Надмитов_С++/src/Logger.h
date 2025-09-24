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
 * @brief ����� ��� ����������������� ����������� � ����.
 *
 * ����� ������������� ������ ��� ������ ��������� ����� ��������� � ���-����:
 * - ����������� ����������� ������
 * - ������ ��� ������ �������
 * - �������������� ���������
 *
 * ��� �������� ������ �������� ��������� ��� ���������� ������ � ������������� �����.
 * ������ ������: [���] ����� | �������������� ����������
 */
class SCANNER_API Logger {
private:
    std::ofstream log_file;       ///< �������� ����� ��� ������ �����
    std::mutex log_mutex;         ///< ������� ��� ����������� ������������������

public:
    /**
     * @brief ����������� ������ Logger.
     * @param[in] filename ���� � ����� ��� ������ �����.
     * @throws std::runtime_error ���� �� ������� ������� ���� ��� ������.
     */
    Logger(const std::string& filename);

    /**
     * @brief ���������� � ��� ���������� �� ����������� ������������ �����.
     * @param[in] file_path ���� � ������������� �����.
     * @param[in] hash MD5-��� ����������� �����.
     * @param[in] verdict ������� (��� ������) ��� ������� ����.
     * @throws std::ios_base::failure ��� ������ ������ � ����.
     *
     * @example
     * ������ ������:
     * [DETECTED] 2024-01-15 14:30:25 | File: C:\path\to\file.exe | Hash: a9963513d093ffb2bc7ceb9807771ad4 | Verdict: Exploit
     */
    void logDetection(const std::string& file_path, const std::string& hash,
        const std::string& verdict);

    /**
     * @brief ���������� � ��� ��������� �� ������.
     * @param[in] error ����� ������.
     * @throws std::ios_base::failure ��� ������ ������ � ����.
     *
     * @example
     * ������ ������:
     * [ERROR] 2024-01-15 14:30:25 | Error: No permission to read file: C:\protected\file.exe
     */
    void logError(const std::string& error);

    /**
     * @brief ���������� � ��� �������������� ���������.
     * @param[in] message ����� ��������������� ���������.
     * @throws std::ios_base::failure ��� ������ ������ � ����.
     *
     * @example
     * ������ ������:
     * [INFO] 2024-01-15 14:30:25 | Scan started: path="C:\target_folder" base="malware_db.csv"
     * [INFO] 2024-01-15 14:30:25 | Threads: 4 | Recursive: true
     */
    void logInfo(const std::string& message);

    /**
     * @brief ���������� ������ Logger.
     * @note ������������� ��������� �������� �����, ���� �� ������.
     */
    ~Logger();
};
#endif // !LOGGER_H