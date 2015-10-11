#include <iostream>
#include "BinaryTree.h"
#include "IntKeysComparer.h"
#include "AsmerTest/AsmerTester.h"
#include "AsmerTest/DefaultTestStatisticsPrinter.h"
#include "TreeTests.h"
#include <fstream>

using namespace std;

int main(int argumentsCount, char * argumentValues[]) {
	const int InitialSize = 10000;
	const int SizeIncrement = 10000;
	const int TestsCount = 3;

	queue<IAsmerTest *> orderedTests;
	queue<IAsmerTest *> randomTests;

	int size = InitialSize;
	for(int i = 0; i < TestsCount; i++) {
		orderedTests.push(new InsertTest(size, true));
		size += SizeIncrement;
	}

	size = InitialSize;
	for(int i = 0; i < TestsCount; i++) {
		randomTests.push(new InsertTest(size, false));
		size += SizeIncrement;
	}

	AsmerTester tester;
	DefaultTestStatisticsPrinter * printer = new DefaultTestStatisticsPrinter("; ");

	tester.RunTests(orderedTests);
	tester.PrintReport();
	tester.PrintStatistics(printer, new ofstream("ordered.csv"));

	cerr << endl << "==================================================" << endl << endl;

	tester.RunTests(randomTests);
	tester.PrintReport();
	tester.PrintStatistics(printer, new ofstream("random.csv"));
	return 0;
}
