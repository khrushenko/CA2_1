#ifndef _I_ASMER_TEST_
#define _I_ASMER_TEST_

class IAsmerTest {
public:
	virtual void PrepareTest() = 0;
	virtual void RunTest() = 0;
	virtual void Finalize() = 0;
	virtual string TestLabel() const = 0;
	virtual int TestSize() const = 0;
};

#endif