#ifndef _ASMER_TEST_RESULT_
#define _ASMER_TEST_RESULT_

#include <cstring>
#include <stdlib.h>
using namespace std;

struct AsmerTestResult {
	string Label;
	int TestSize;
	ULONG64 StartCyclesTime;
	ULONG64 EndCyclesTime;
	ULONG64 DurationCyclesTime;

	AsmerTestResult(string label, int testSize, ULONG64 startCyclesTime, ULONG64 endCyclesTime) {
		Label = label;
		TestSize = testSize;
		StartCyclesTime = startCyclesTime;
		EndCyclesTime = endCyclesTime;
		DurationCyclesTime = EndCyclesTime - StartCyclesTime;
	}

	string ToString() {
		return Label + ": " + LongLongToString(DurationCyclesTime) + " [nanoseconds]";
	}

	string LongLongToString(ULONG64 value) {
		string accumulator = "";
		do
		{
			accumulator += (char)('0' + value % 10);
			value /= 10;
		} while(value > 0);
		char buffer[32];
		strcpy(buffer, accumulator.c_str());
		int length = strlen(buffer);
		for(int i = 0; i < length / 2; i++)
		{
			char c = buffer[i];
			buffer[i] = buffer[length - i - 1];
			buffer[length - i - 1] = c;
		}
		return string(buffer);
	}
};

#endif
