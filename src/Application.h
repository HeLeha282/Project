#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include "Report.h"

// Макрос для экспорта/импорта
#ifdef SCANNER_LIBRARY_EXPORTS
#define SCANNER_API __declspec(dllexport)
#else
#define SCANNER_API __declspec(dllimport)
#endif

class SCANNER_API Application {
public:
	Report run(const std::string& base, const std::string& log, const std::string& path);
};


#endif // !APPLICATION_H
