#include <iostream>
#include "Application.h"
#include <chrono>

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru_RU");
	std::string hash_base_path = "hash_base_path";
	std::string log_file = "log_file";
	std::string scan_dir_path = "scan_dir_path";

	for (int i = 1; i < argc; i++) {
		std::string arg = argv[i]; // преобразуем в std::string
		if (arg == "--base") {
			//std::cout << arg << std::endl;
			if (i + 1 < argc) {
				hash_base_path = argv[i + 1];
				i++;
			}
		}
		else if (arg == "--log") {
			//std::cout << arg << std::endl;
			if (i + 1 < argc) {
				log_file = argv[i + 1];
				i++;
			}
		}
		else if (arg == "--path") {
			//std::cout << arg << std::endl;
			if (i + 1 < argc) {
				scan_dir_path = argv[i + 1];
				i++;
			}
		}
	}

	if (hash_base_path == "hash_base_path" || log_file == "log_file" || scan_dir_path == "scan_dir_path") {
		std::cerr << "Usage: " << argv[0] << " --base <hash_db> --log <log_file> --path <scan_dir>\n";
		std::cerr << "Example: scanner.exe --base hashes.csv --log scan.log --path C:\\Windows\n";
		return 1;
	}

	//std::cout << hash_base_path << '\n';
	//std::cout << log_file << '\n';
	//std::cout << scan_dir_path << '\n';

	try {
		auto start = std::chrono::steady_clock::now();
		std::cout << "Utility started working..." << std::endl;
		Application app;
		Report report = app.run(hash_base_path, log_file, scan_dir_path);

		auto end = std::chrono::steady_clock::now();

		std::chrono::duration<double> elapsed = end - start;
		double duration_sec = elapsed.count();
		report.setElapsedTime(duration_sec);
		report.printReport();

		return 0;
	}
	catch (const std::exception& e) {
		std::cerr << "Fatal error: " << e.what() << '\n';
		return 1;
	}
}

