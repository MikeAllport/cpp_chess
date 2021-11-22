// cppchessengine.cpp : Defines the entry point for the application.
//

#include "cppchess.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	VectorHelper<int> list;
	list.v = { 1, 2, 3, 4, 5 };
	auto newList = list.Filter([](int a) { return a == 1 || a == 2; });
	for (int a : newList.v)
	{
		std::cout << a << endl;;
	}
	return 0;
}
