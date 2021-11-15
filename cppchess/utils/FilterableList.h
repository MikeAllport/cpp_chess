#ifndef FILTERABLE_LIST
#define FILTERABLE_LIST

#include <vector>
#include <functional>
#include <algorithm>

template <class T>
class FilterableList
{
public:
	FilterableList() : v() {}
	FilterableList<T> Filter(std::function<bool(T)> comparitor);
	bool Contains(T other) { return std::find(std::begin(v), std::end(v), other) != std::end(v);}
	FilterableList<T>& Concatenate(FilterableList<T>& other) {
		for(T ele: other.v)
		{
			v.push_back(ele);
		}
		return *this;
	}
	std::vector<T> v;
};

template <class T>
FilterableList<T> FilterableList<T>::Filter(std::function<bool(T)> comparitor) {
	FilterableList<T> newList;
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