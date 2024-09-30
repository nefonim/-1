#include "Novel.hpp"
#include <iostream>

using book::Novel;

Novel::Novel(std::string name, attrs::FullName author,
		     attrs::Lifespan author_lifespan, Array<std::string> notable_works,
		     std::string biography)
:	Book(std::move(name))
,	author(std::move(author))
,	lifespan(std::move(author_lifespan))
,	notable_works(std::move(notable_works))
,	biography(std::move(biography)) {
	std::cerr << "Создана информация о романисте: " << this->author << ".\n";
}

Novel::~Novel() {
	std::cerr << "Уничтожена информация о романисте: " << this->author << ".\n";
}

void Novel::about_author(std::ostream &out) const {
	out << this->author << ' ' << this->lifespan << '\n';
	out << "Основные романы:\n";
	for (size_t i = 0; i < this->notable_works.len; ++i) {
		out << i + 1 << ".\t" << this->notable_works.ptr[i] << '\n';
	}
	out << this->biography;
}
