#include <iostream>
#include <string>
#include <limits>
#include <utility>
#include "Publication.hpp"
#include "attrs/FullName.hpp"
#include "attrs/Lifespan.hpp"
#include "book/Fiction.hpp"
#include "book/Novel.hpp"
#include "book/Poem.hpp"
#include "collections/Array.hpp"

using book::Poem;
using book::Novel;
using book::Fiction;

static inline void strip_newline(std::istream &stream) {
	stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Publication::Publication() {
	std::cerr << "Создано книжное издание.\n";
}

void Publication::operator=(Publication &&other) {
	this->clear();
	this->books = other.books;
	other.books = nullptr;
}

Publication::~Publication() {
	this->clear();
	std::cerr << "Уничтожено книжное издание.\n";
}

void Publication::clear() {
	while (this->books) this->erase();
}

static Book *book_list_value(const LinkedList<Book *> *list) {
	return list ? list->value : nullptr;
}

const Book *Publication::current() const {
	return book_list_value(this->books);
}

const Book *Publication::prev() const {
	const auto current = this->books;
	return current ? book_list_value(current->prev) : nullptr;
}

const Book *Publication::next() const {
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

constexpr auto POEM = "Поэма";
constexpr auto NOVEL = "Роман";
constexpr auto FICTION = "Фантастика";
constexpr auto END = "Конец";

static std::string load_name(std::istream &file) {
	std::string name;
	std::getline(file, name);
	return name;
}

static attrs::FullName load_author(std::istream &file) {
	attrs::FullName author;
	file >> author.first >> author.middle >> author.last;
	return author;
}

static attrs::Lifespan load_lifespan(std::istream &file) {
	attrs::Lifespan result;
	file >> result.born >> result.died;
	return result;
}

static Array<std::string> load_works(std::istream &file) {
	size_t n;
	file >> n;
	strip_newline(file);

	auto result = Array<std::string>(n);
	for (size_t i = 0; i < n; ++i) {
		std::getline(file, result.ptr[i]);
	}
	return result;
}

static Poem *load_book_poem(std::istream &file) {
	auto name = load_name(file);
	auto author = load_author(file);
	const auto lifespan = load_lifespan(file);
	auto works = load_works(file);
	if (!file) return nullptr;

	return new Poem(std::move(name), std::move(author),
	                lifespan, std::move(works));
}

static std::string load_biography(std::istream &file) {
	std::string result;
	while (true) {
		std::string newline;
		std::getline(file, newline);
		if (newline.empty()) break;
		result = result + newline + '\n';
	}
	return result;
}

static Novel *load_book_novel(std::istream &file) {
	auto name = load_name(file);
	auto author = load_author(file);
	const auto lifespan = load_lifespan(file);
	auto works = load_works(file);
	auto biography = load_biography(file);
	if (!file) return nullptr;

	return new Novel(std::move(name), std::move(author),
	                 lifespan, std::move(works), std::move(biography));
}

static bool load_is_filmed(std::istream &file) {
	bool result;
	file >> result;
	return result;
}

static Fiction *load_book_fiction(std::istream &file) {
	auto name = load_name(file);
	auto author = load_author(file);
	const auto is_filmed = load_is_filmed(file);
	auto works = load_works(file);
	if (!file) return nullptr;

	return new Fiction(std::move(name), std::move(author),
	                   std::move(works), is_filmed);
}

bool Publication::load(std::istream &file) {
	while (true) {
		std::string type;
		std::getline(file, type);

		Book *book;
		if (type == POEM) {
			book = load_book_poem(file);
		} else if (type == NOVEL) {
			book = load_book_novel(file);
		} else if (type == FICTION) {
			book = load_book_fiction(file);
		} else if (type == END) {
			break;
		} else {
			return false;
		}

		if (!book) return false;
		this->insert(book);
	}

	size_t m;
	file >> m;
	if (!this->books) return m == 0;

	while (m--) {
		const auto next = this->books->next;
		if (!next) return false;
		this->books = next;
	}

	return true;
}

static void store_author(const attrs::FullName &value, std::ostream &file) {
	file << value.first << ' ' << value.middle << ' ' << value.last << '\n';
}

static void store_lifespan(const attrs::Lifespan &value, std::ostream &file) {
	file << value.born << ' ' << value.died << '\n';
}

static void store_works(const Array<std::string> &value, std::ostream &file) {
	file << value.len << '\n';
	for (size_t i = 0; i < value.len; ++i) {
		file << value.ptr[i] << '\n';
	}
}

static void store_book_poem(const Poem &value, std::ostream &file) {
	file << POEM << '\n' << value.get_name() << '\n';
	store_author(value.author, file);
	store_lifespan(value.lifespan, file);
	store_works(value.notable_works, file);
}

static void store_book_novel(const Novel &value, std::ostream &file) {
	file << NOVEL << '\n' << value.get_name() << '\n';
	store_author(value.author, file);
	store_lifespan(value.lifespan, file);
	store_works(value.notable_works, file);
	file << value.biography << '\n';
}

static void store_book_fiction(const Fiction &value, std::ostream &file) {
	file << FICTION << '\n' << value.get_name() << '\n';
	store_author(value.author, file);
	file << (value.is_filmed ? '1' : '0') << '\n';
	store_works(value.notable_works, file);
}

void Publication::store(std::ostream &file) const {
	const auto *book = this->books;
	size_t k = -1;
	if (book) {
		while (true) {
			++k;
			const auto next = book->next;
			if (!book->next) break;
			book = next;
		}
	}

	size_t n = 0;
	while (book) {
		const auto *const value = book->value;
		if (const auto poem = dynamic_cast<const Poem *>(value)) {
			store_book_poem(*poem, file);
		} else if (const auto novel = dynamic_cast<const Novel *>(value)) {
			store_book_novel(*novel, file);
		} else if (const auto fiction = dynamic_cast<const Fiction *>(value)) {
			store_book_fiction(*fiction, file);
		} else {
			// Для нашей программы определено лишь 3 наследника Book
			std::unreachable();
		}
		book = book->prev;
		++n;
	}

	const size_t m = n - k - 1;
	file << END << '\n' << m;
}
