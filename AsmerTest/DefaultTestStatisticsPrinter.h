#ifndef _DEFAULT_TEST_STATISTICS_PRINTER_
#define _DEFAULT_TEST_STATISTICS_PRINTER_

#include "ITestStatisticsPrinter.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class DefaultTestStatisticsPrinter : public ITestStatisticsPrinter {
	string splitter;
public:
	DefaultTestStatisticsPrinter(string splitter) {
		this->splitter = splitter;
	}

	virtual string ToStatistics(AsmerTestResult result) const {
		char buffer[32] = {0};
		sprintf(buffer, "%d", result.TestSize);
		return string(buffer) +
			splitter +
			result.LongLongToString(result.DurationCyclesTime);
	}
};

#endif
