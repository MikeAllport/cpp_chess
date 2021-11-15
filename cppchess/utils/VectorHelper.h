#ifndef FILTERABLE_LIST
#define FILTERABLE_LIST

#include <vector>
#include <functional>
#include <algorithm>

template <class T>
class VectorHelper
{
public:
	VectorHelper() : v() {}
	VectorHelper<T> Filter(std::function<bool(T)> comparitor);
	bool Contains(T other) { return std::find(std::begin(v), std::end(v), other) != std::end(v);}
	VectorHelper<T>& Concatenate(VectorHelper<T>& other) {
		for(T ele: other.v)
		{
			v.push_back(ele);
		}
		return *this;
	}
	std::vector<T> v;
};

template <class T>
VectorHelper<T> VectorHelper<T>::Filter(std::function<bool(T)> comparitor) {
	VectorHelper<T> newList;
	for (std::vector<T>::iterator it = v.begin(); it != v.end(); ++it)
	{
		if (comparitor(*it))
		{
			newList.v.push_back(*it);
		}
	}
	return newList;
}

#endif