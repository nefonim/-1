#include <iostream>
#include <string>
#include <limits>

#include "Publication.hpp"
#include "attrs/FullName.hpp"
#include "attrs/Lifespan.hpp"
#include "book/Fiction.hpp"
#include "book/Novel.hpp"
#include "book/Poem.hpp"

using book::Fiction;
using book::Novel;
using book::Poem;

void strip_newline(std::istream &stream) {
	stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

enum class Genre {
	Poem,
	Novel,
	Fiction,
};

Genre ask_genre() {
	std::cout << "Жанр (поэма|роман|фантастика): ";

	std::string genre_string;
	std::getline(std::cin, genre_string);

	if (genre_string == "поэма") {
		return Genre::Poem;
	} else if (genre_string == "роман") {
		return Genre::Novel;
	} else if (genre_string == "фантастика") {
		return Genre::Fiction;
	} else {
		std::cerr << "Неопознанный жанр.\n";
		std::exit(1);
	}
}

attrs::FullName ask_author() {
	std::cout << "Полное имя автора: ";

	attrs::FullName result;
	std::getline(std::cin, result.first, ' ');
	std::getline(std::cin, result.middle, ' ');
	std::getline(std::cin, result.last);
	return result;
}

attrs::Lifespan ask_lifespan() {
	attrs::Lifespan result;

	std::cout << "Год рождения автора: ";
	std::cin >> result.born;

	std::cout << "Год смерти автора: ";
	std::cin >> result.died;

	strip_newline(std::cin);
	return result;
}

Array<std::string> ask_notable_works() {
	std::cout << "Количество работ: ";
	size_t len;
	std::cin >> len;
	strip_newline(std::cin);

	auto result = Array<std::string>(len);
	std::cout << "Названия работ (" << len << " шт.):\n";
	for (size_t i = 0; i < len; ++i) {
		std::getline(std::cin, result.ptr[i]);
	}
	return result;
}

bool ask_if_filmed() {
	std::cout << "Были ли сняты фильмы по перечисленным книгам? [+/-] ";
	char answer = std::cin.get();
	if (answer != '\n') strip_newline(std::cin);
	return answer == '+';
}

Fiction ask_book_fiction(std::string name) {
	auto author = ask_author();
	auto works = ask_notable_works();
	const auto is_filmed = ask_if_filmed();
	return Fiction(std::move(name), std::move(author),
	               std::move(works), is_filmed);
}

std::string ask_biography() {
	std::cout << "Краткая биография (до пустой строки):\n";
	std::string result;

	while (true) {
		std::string newline;
		std::getline(std::cin, newline);
		if (newline.empty()) break;
		result = result + '\n' + newline;
	}
	return result;
}

Novel ask_book_novel(std::string name) {
	auto author = ask_author();
	auto lifespan = ask_lifespan();
	auto works = ask_notable_works();
	auto biography = ask_biography();

	return Novel(std::move(name), std::move(author),
	             std::move(lifespan), std::move(works), std::move(biography));
}

Poem ask_book_poem(std::string name) {
	auto author = ask_author();
	auto lifespan = ask_lifespan();
	auto works = ask_notable_works();

	return Poem(std::move(name), std::move(author),
	            std::move(lifespan), std::move(works));
}

Book *ask_new_book() {
	const auto genre = ask_genre();

	std::cout << "Название книги: ";
	std::string book_name;
	std::getline(std::cin, book_name);

	Book *result;
	switch (genre) {
	case Genre::Fiction:
		result = new Fiction(ask_book_fiction(std::move(book_name)));
		break;
	case Genre::Novel:
		result = new Novel(ask_book_novel(std::move(book_name)));
		break;
	case Genre::Poem:
		result = new Poem(ask_book_poem(std::move(book_name)));
		break;
	}
	return result;
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
