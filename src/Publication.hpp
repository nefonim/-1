#pragma once

#include <iostream>

#include "collections/LinkedList.hpp"
#include "Book.hpp"

using collections::LinkedList;

class Publication {
	LinkedList<Book *> *books = nullptr;
public:
	explicit Publication();
	~Publication();

	const Book *current();
	const Book *next();
	const Book *prev();

	void scroll_next();
	void scroll_prev();

	void insert(Book *value);
	void erase();

	void clear();

	void load(std::istream &file);
	void store(std::ostream &file);
};
