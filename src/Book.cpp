#include <iostream>
#include "Book.hpp"

const std::string &Book::get_name() const {
	return this->name;
}

Book::Book(std::string &&name) : name(name) {
	std::cerr << "Создана новая книга: " << this->name << ".\n";
}

Book::~Book() {
	std::cerr << "Уничтожена книга: " << this->name << ".\n";
}
