#include "Poem.hpp"
#include <iostream>

using book::Poem;

Poem::Poem(std::string name, attrs::FullName author,
		     attrs::Lifespan author_lifespan, Array<std::string> notable_works)
:	Book(std::move(name))
,	author(std::move(author))
,	lifespan(std::move(author_lifespan))
,	notable_works(std::move(notable_works)) {
	std::cerr << "Создана информация о поэте: " << this->author << ".\n";
}

Poem::~Poem() {
	std::cerr << "Уничтожена информация о поэте: " << this->author << ".\n";
}

void Poem::about_author(std::ostream &out) const {
	out << this->author << ' ' << this->lifespan << '\n';
	out << "Основные поэмы:\n";
	for (size_t i = 0; i < this->notable_works.len; ++i) {
		out << i + 1 << ".\t" << this->notable_works.ptr[i] << '\n';
	}
}
