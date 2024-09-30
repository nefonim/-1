#pragma once

#include "Book.hpp"
#include "attrs/FullName.hpp"
#include "collections/Array.hpp"
#include <string>

namespace book {
	struct Fiction final : public Book {
		attrs::FullName author;
		Array<std::string> notable_works;
		bool is_filmed;
		Fiction(std::string name, attrs::FullName author,
		        Array<std::string> notable_works, bool is_filmed);
		~Fiction();
		void about_author(std::ostream &out) const final;
	};
}
