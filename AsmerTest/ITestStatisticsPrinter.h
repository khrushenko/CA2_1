#ifndef _I_TEST_STATISTICS_PRINTER_
#define _I_TEST_STATISTICS_PRINTER_

#include "AsmerTestResult.h"
#include <string>
using namespace std;

class ITestStatisticsPrinter {
public:
	virtual string ToStatistics(AsmerTestResult result) const = 0;
};

#endif