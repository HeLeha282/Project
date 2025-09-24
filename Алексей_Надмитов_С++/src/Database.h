#ifndef DATABASE_H
#define DATABASE_H
#include <unordered_map>
#include <string>
#ifdef SCANNER_LIBRARY_EXPORTS
#define SCANNER_API __declspec(dllexport)
#else
#define SCANNER_API __declspec(dllimport)
#endif
/**
 * @brief ����� ��� ������ � ����� ����������� �����.
 *
 * ��������� ���� � ��������������� �� �������� �� CSV-����� � �������������
 * ��������� ��� �������� ����� �� ������� � ����.
 *
 * @class Database
 */
class SCANNER_API Database {
public:
    /**
     * @brief �����������, ����������� ���� �� CSV-�����.
     *
     * @param csvFilePath ���� � CSV-����� � ������ � ����������.
     *
     * @throws std::runtime_error ���� ���� �� ����������, ���������� ��� ������
     *                            ��� ����� ������������ ������.
     *
     * @see load()
     */
    Database(const std::string& csvFilePath);

    /**
     * @brief ���������, ���������� �� ��� � ���� �����������.
     *
     * @param hash MD5-��� ����� � ���� ������ (� ������ ��������, ��� ������������).
     * @return std::string ������� �� ����, ���� ��� ������; ����� � ������ ������.
     *
     */
    std::string getVerdict(std::string hash);

private:
    /**
     * @brief ��������� ������ �� CSV-����� � ������.
     *
     * ������ CSV: ������ ������ �������� ��� � �������, ����������� �������� ';'.
     * ������ ������ ������������. ���������� ������� ������ ���� � �������� ����������.
     *
     * @param csvFilePath ���� � CSV-�����.
     *
     * @throws std::runtime_error ��� ������� ������ ��� �������� �����.
     *
     * @see StringUtils::trim()
     */
    void load(const std::string& csvFilePath);

    std::unordered_map<std::string, std::string> maliciousHashes; ///< ��������� ����� � ���������
};

#endif // !DATABASE_H