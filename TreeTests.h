#ifndef _TREE_TESTS_
#define _TREE_TESTS_

#include "AsmerTest/IAsmerTest.h"
#include "IntKeysComparer.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

class InsertTest : public IAsmerTest {
	BinaryTree<int, int> * tree;
	int size;
	bool orderedValues;
	int * valuesToInsert;
public:
	InsertTest(int size, bool orderedValues) {
		tree = new BinaryTree<int, int>(new IntKeysComparer());
		this->size = size;
		this->orderedValues = orderedValues;
	}

	~InsertTest() {
		delete tree;
	}

	virtual void PrepareTest() {
		valuesToInsert = new int [size];
		srand(time(0));
		for(int i = 0; i < size; i++)
			valuesToInsert[i] = (orderedValues ? i : rand());
	}

	virtual void Finalize() {
		delete [] valuesToInsert;
	}

	virtual void RunTest() {
		for(int i = 0; i < size; i++)
			tree->InsertAnyway(valuesToInsert[i], valuesToInsert[i]);
	}

	virtual int TestSize() const {
		return size;
	}

	virtual string TestLabel() const {
		char buffer[32] = { 0 };
		sprintf(buffer, "%d", size);
		return string("Insert ") + buffer + (orderedValues ? " ordered " : " random ") + "values";
	}
};

#endif
