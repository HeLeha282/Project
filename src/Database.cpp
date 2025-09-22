#include "Database.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include "StringUtils.h"
#include <regex>
Database::Database(const std::string& csvFilePath)
{
	load(csvFilePath);
}

void Database::load(const std::string& csvFilePath)
{
	//std::cout << std::filesystem::current_path()<<std::endl;
	if (!std::filesystem::exists(csvFilePath)) {
		throw std::runtime_error("CSV ���� �� ����������: " + csvFilePath);
	}

	// �������� ��� ��� ������� ����
	if (!std::filesystem::is_regular_file(csvFilePath)) {
		throw std::runtime_error("���� �� �������� ������: " + csvFilePath);
	}

	std::ifstream inf(csvFilePath);

	if (!inf.is_open()) {
		// ��������� ��� ������ ��� ����� ������� ���������
		if (errno == EACCES) {
			throw std::runtime_error("������������ ���� ��� ������ �����: " + csvFilePath);
		}
		else {
			throw std::runtime_error("������ �������� �����: " + csvFilePath);
		}
	}
	std::string line;
	size_t delimiterPos;
	std::string hash;
	std::string verdict;
	while (std::getline(inf, line)) {
		if (line.empty()) continue; // ���������� ������ ������
		//std::cout << line << " sdada" << std::endl;
		delimiterPos = line.find(';');
		if (delimiterPos == std::string::npos) {
			throw std::runtime_error("������������ ������ CSV �����: " + line);
		}

		hash = StringUtils::trim(line.substr(0, delimiterPos));
		verdict = StringUtils::trim(line.substr(delimiterPos + 1));
		maliciousHashes[hash] = verdict;
	}

	/*
	for (const std::pair<std::string, std::string> pair : maliciousHashes) {
		std::cout << pair.first << " -> " << pair.second <<std::endl;
	}
	*/

	
}

std::string Database::getVerdict(std::string hash)
{
	std::string result = "";
	std::unordered_map<std::string, std::string>::const_iterator it = maliciousHashes.find(hash);
	if (it != maliciousHashes.end()) {
		result = it->second;
	}
	return result;
}
