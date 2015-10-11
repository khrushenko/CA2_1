#ifndef _INT_KEYS_COMPARER_
#define _INT_KEYS_COMPARER_

#include "IKeysComparer.h"
#include <math.h>

class IntKeysComparer : public IKeysComparer<int> {
public:
	virtual int Compare(const int & firstKey, const int & secondKey) const {
		double firstCos = cos(M_PI * firstKey / 180.0);
		double secondCos = cos(M_PI * secondKey / 180.0);
		double delta = firstCos - secondCos;
		if(delta == 0.0)
			return 0;
		return (delta < 0 ? -1 : 1);
	}
};

#endif
