#ifndef _ASMER_TEST_
#define _ASMER_TEST_

#define ULONG64 long long int

#include <stdlib.h>
#include <queue>
#include <iostream>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "AsmerTestResult.h"
#include "IAsmerTest.h"
#include "ITestStatisticsPrinter.h"

using namespace std;

class AsmerTester {
	vector<AsmerTestResult> testResults;
	queue<IAsmerTest *> tests;
public:
	void RunTests(queue<IAsmerTest *> tests) {
		this->tests = tests;
		testResults.clear();
		while(!this->tests.empty())
			RunNextTest();
	}

	void PrintReport(ostream * out = 0) {
		if(out == 0)
			out = &cerr;
		for(int i = 0; i < testResults.size(); i++)
			(* out) << testResults[i].ToString() << endl;
	}

	void PrintStatistics(ITestStatisticsPrinter * printer, ostream * out = 0) {
		if(out == 0)
			out = &cerr;
		for(int i = 0; i < testResults.size(); i++)
			(* out) << printer->ToStatistics(testResults[i]) << endl;
	}

private:
	void RunNextTest() {
		IAsmerTest * test = tests.front();
		ULONG64 startNanos = 0, endNanos = 0;
		test->PrepareTest();
		timespec startTime, endTime;
		sysconf(_POSIX_THREAD_CPUTIME);
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &startTime);
		startNanos = (ULONG64)(startTime.tv_sec) * 1000000000 + startTime.tv_nsec;
		test->RunTest();
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &endTime);
		endNanos = (ULONG64)(endTime.tv_sec) * 1000000000 + endTime.tv_nsec;
		test->Finalize();
		tests.pop();
		testResults.push_back(AsmerTestResult(test->TestLabel(), test->TestSize(), startNanos, endNanos));
	}
};

#endif
