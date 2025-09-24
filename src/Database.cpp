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
	if (!std::filesystem::exists(csvFilePath)) {
		throw std::runtime_error("CSV файл не существует: " + csvFilePath);
	}

	// Проверка что это обычный файл
	if (!std::filesystem::is_regular_file(csvFilePath)) {
		throw std::runtime_error("Путь не является файлом: " + csvFilePath);
	}

	std::ifstream inf(csvFilePath);

	if (!inf.is_open()) {
		// Проверяем код ошибки для более точного сообщения
		if (errno == EACCES) {
			throw std::runtime_error("Недостаточно прав для чтения файла: " + csvFilePath);
		}
		else {
			throw std::runtime_error("Ошибка открытия файла: " + csvFilePath);
		}
	}
	std::string line;
	size_t delimiterPos;
	std::string hash;
	std::string verdict;
	while (std::getline(inf, line)) {
		if (line.empty()) continue; // Пропускаем пустые строки
		delimiterPos = line.find(';');
		if (delimiterPos == std::string::npos) {
			throw std::runtime_error("Некорректный формат CSV файла: " + line);
		}

		hash = StringUtils::trim(line.substr(0, delimiterPos));
		verdict = StringUtils::trim(line.substr(delimiterPos + 1));
		maliciousHashes[hash] = verdict;
	}
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
