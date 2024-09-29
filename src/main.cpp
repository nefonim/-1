#include <iostream>
#include "Publication.hpp"

void strip_newline(std::istream &stream) {
	char c;
	do c = stream.get(); while (!stream.eof() && c != '\n');
}

Book *ask_new_book() {
	// TODO
	std::abort();
}

char ask_action() {
	const char result = std::cin.get();
	if (std::cin.eof()) std::exit(0);
	if (result != '\n') strip_newline(std::cin);
	return result;
}

int main() {
	auto publication = Publication();
	while (true) {
		std::cout << "Изданные книги:\n";
		const auto prev = publication.prev();
		const auto curr = publication.current();
		const auto next = publication.next();
		if (prev) std::cout << "...\n   " << prev->get_name() << '\n';
		if (curr) std::cout << " * " << curr->get_name() << '\n';
		if (next) std::cout << "   " << next->get_name() << "\n...\n";

		std::cout << "Действия:\n";
		if (prev) std::cout << "k - просмотреть предыдущую книгу\n";
		if (curr) std::cout << "d - снять текущую книгу с публикации\n";
		if (curr) std::cout << "a - вывести информацию об авторе\n";
		if (next) std::cout << "j - просмотреть следующую книгу\n";
		std::cout <<
			"i - опубликовать новую книгу\n"
			"w - сохранить каталог изданных книг в файле\n"
			"o - восстановить каталог изданных книг из файла\n";

		std::cout << ">>> ";
		const char action = ask_action();

		switch (action) {
		case 'k':
			if (!prev) return 1;
			publication.scroll_prev();
			break;
		case 'd':
			if (!curr) return 1;
			publication.erase();
			break;
		case 'a':
			if (!curr) return 1;
			curr->about_author(std::cout);
			break;
		case 'j':
			if (!next) return 1;
			publication.scroll_next();
			break;
		case 'i': {
			const auto book = ask_new_book();
			if (!book) return 1;
			publication.insert(book);
			break;
		}
		case 'w':
			// TODO
			break;
		case 'o':
			// TODO
			break;
		default:
			return 1;
		}
	}
}
