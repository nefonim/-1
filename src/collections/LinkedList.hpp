#pragma once

namespace collections {
	template<class T>
	struct LinkedList;
}

template<class T>
struct collections::LinkedList {
	T value;
	LinkedList<T> *next, *prev;
};
