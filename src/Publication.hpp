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

	void operator=(Publication &&);

	const Book *current() const;
	const Book *next() const;
	const Book *prev() const;

	void scroll_next();
	void scroll_prev();

	void insert(Book *value);
	void erase();

	void clear();

	bool load(std::istream &file);
	void store(std::ostream &file) const;
};
