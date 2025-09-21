#include "Database.h"
#include <fstream>
#include <iostream>
#include "StringUtils.h"
#include <regex>
void Database::load(const std::string& csvFilePath)
{
	std::ifstream inf;
	inf.open(csvFilePath);
	//if (!inf) {
	//	std::cout << "ошибка потока";
	//	
	//}
	if (!inf.is_open()) {
		//std::cout << "ошибка чтения файла";
		throw std::runtime_error("ошибка чтения CSV файла " + csvFilePath);
	}
	std::string line;
	size_t delimiterPos;
	std::string hash;
	std::string verdict;
	while (std::getline(inf, line)) {
		if (line.empty()) continue; // Пропускаем пустые строки
		std::cout << line << " sdada" << std::endl;
		delimiterPos = line.find(';');
		if (delimiterPos == std::string::npos) {
			throw std::runtime_error("Некорректный формат CSV файла: " + line);
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

std::string Database::isMalicious(std::string hash)
{
	std::string result = "";
	std::unordered_map<std::string, std::string>::const_iterator it = maliciousHashes.find(hash);
	if (it != maliciousHashes.end()) {
		result = it->second;
	}
	return result;
}
