
#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include "Report.h"

class Application {
public:
	Report run(const std::string& base, const std::string& log, const std::string& path);
};


#endif // !APPLICATION_H
