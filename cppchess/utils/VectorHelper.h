#ifndef FILTERABLE_LIST
#define FILTERABLE_LIST

#include <vector>
#include <functional>
#include <algorithm>

// VectorHelper is a vector wrapper to facilitate commonly used functions that vector
// class does not have
template <class T>
class VectorHelper
{
public:
	VectorHelper() : v() {}

	// simple filter method, takes comparitor function as parameter, returns only items
	// in vector that the comparitor returns true
	VectorHelper<T> Filter(std::function<bool(T)> comparitor);

	T FirstOrNull(std::function<bool(T)> comparitor);

	// simple contains method, returns boolean if parameter exists is vector. T must implement
	// operator==
	bool Contains(T other) { return std::find(std::begin(v), std::end(v), other) != std::end(v);}

	// simple concatenate method, adds all the elements from others vector and returns itself
	VectorHelper<T>& Concatenate(VectorHelper<T> other) {
		for(T ele: other.v)
		{
			v.push_back(ele);
		}
		return *this;
	}
	std::vector<T> v;
};

// implementation for Filter
template <class T>
VectorHelper<T> VectorHelper<T>::Filter(std::function<bool(T)> comparitor) {
	VectorHelper<T> newList;
	for (typename std::vector<T>::iterator it = v.begin(); it != v.end(); ++it)
	{
		if (comparitor(*it))
		{
			newList.v.push_back(*it);
		}
	}
	return newList;
}

template <class T>
T VectorHelper<T>::FirstOrNull(std::function<bool(T)> comparitor) {
	for (typename std::vector<T>::iterator it = v.begin(); it != v.end(); ++it)
	{
		if (comparitor(*it))
		{
			return *it;
		}
	}
	return nullptr;
}

#endif