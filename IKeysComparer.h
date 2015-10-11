#ifndef _I_KEYS_COMPARER_
#define _I_KEYS_COMPARER_

template <typename TKey>
class IKeysComparer {
public:
	virtual int Compare(const TKey & firstKey, const TKey & secondKey) const = 0;
};

#endif