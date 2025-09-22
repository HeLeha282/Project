#include "Report.h"

void Report::addFileProcessed()
{
	totalFiles += 1;
}

void Report::addInfected()
{
	infectedFiles += 1;
}

void Report::addError()
{
	errors += 1;
}

void Report::setElapsedTime(double seconds)
{
	elapsedTime = seconds;
}
