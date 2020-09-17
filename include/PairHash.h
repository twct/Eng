#ifndef __PAIRHASH_H__
#define __PAIRHASH_H__

#include <functional>
#include <cstddef>

struct PairHash
{
	template <class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2> &pair) const
	{
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

#endif