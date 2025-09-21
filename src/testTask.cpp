#include <iostream>
#include "Application.h"

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru_RU");
	std::string hash_base_path = "hash_base_path";
	std::string log_file = "log_file";
	std::string scan_dir_path = "scan_dir_path";

	for (int i = 1; i < argc; i++) {
		std::string arg = argv[i]; // Преобразуем в std::string
		if (arg == "--base") {
			std::cout << arg << std::endl;
			if (i + 1 < argc) {
				hash_base_path = argv[i + 1];
				i++;
			}
		}
		else if (arg == "--log") {
			std::cout << arg << std::endl;
			if (i + 1 < argc) {
				log_file = argv[i + 1];
				i++;
			}
		}
		else if (arg == "--path") {
			std::cout << arg << std::endl;
			if (i + 1 < argc) {
				scan_dir_path = argv[i + 1];
				i++;
			}
		}
	}

	std::cout << hash_base_path << '\n';
	std::cout << log_file << '\n';
	std::cout << scan_dir_path << '\n';

	try {
		Application app;
		app.run(hash_base_path, log_file, scan_dir_path);
	}
	catch (const std::runtime_error& e) {
		std::cout << e.what() << '\n';
	}
}

