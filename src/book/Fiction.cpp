#include "Fiction.hpp"
#include <iostream>

using book::Fiction;

Fiction::Fiction(std::string name, attrs::FullName author,
                 Array<std::string> notable_works, bool is_filmed)
:	Book(std::move(name))
,	author(std::move(author))
,	notable_works(std::move(notable_works))
,	is_filmed(is_filmed) {
	std::cerr << "Создана информация о фантасте: " << this->author << ".\n";
}

Fiction::~Fiction() {
	std::cerr << "Уничтожена информация о фантасте: " << this->author << ".\n";
}

void Fiction::about_author(std::ostream &out) const {
	out << this->author << '\n';
	out << "Основные произведения фантастики:\n";
	for (size_t i = 0; i < this->notable_works.len; ++i) {
		out << i + 1 << ".\t" << this->notable_works.ptr[i] << '\n';
	}
	if (this->is_filmed) {
		out << "По произведениям этого автора сняты фильмы.\n";
	}
}
