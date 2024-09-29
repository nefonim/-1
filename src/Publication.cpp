#include <iostream>
#include "Publication.hpp"

Publication::Publication() {
	std::cerr << "Создано книжное издание.\n";
}

Publication::~Publication() {
	this->clear();
	std::cerr << "Уничтожено книжное издание.\n";
}

void Publication::clear() {
	if (!this->books) return;
	while (const auto prev = this->books->prev) this->books = prev;
	while (this->books) this->erase();
}

Book *book_list_value(const LinkedList<Book *> *list) {
	return list ? list->value : nullptr;
}

const Book *Publication::current() {
	return book_list_value(this->books);
}

const Book *Publication::prev() {
	const auto current = this->books;
	return current ? book_list_value(current->prev) : nullptr;
}

const Book *Publication::next() {
	const auto current = this->books;
	return current ? book_list_value(current->next) : nullptr;
}

void Publication::scroll_next() {
	this->books = this->books->next;
}

void Publication::scroll_prev() {
	this->books = this->books->prev;
}

void Publication::insert(Book *value) {
	const auto next = this->books;
	const auto node = new LinkedList<Book *> {
		.value = value,
		.next = next,
		.prev = nullptr,
	};

	if (next) {
		const auto prev = next->prev;
		next->prev = node;
		if (prev) {
			prev->next = node;
			node->prev = prev;
		}
	}

	this->books = node;
}

void Publication::erase() {
	const auto deleted = this->books;
	const auto prev = deleted->prev, next = deleted->next;

	delete deleted->value;
	delete deleted;
	if (prev) prev->next = next;
	if (next) next->prev = prev;

	this->books = next ? next : prev;
}
