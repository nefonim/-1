#pragma once

#include "Book.hpp"
#include "attrs/FullName.hpp"
#include "attrs/Lifespan.hpp"
#include "collections/Array.hpp"

namespace book {
	struct Novel final : public Book {
		attrs::FullName author;
		attrs::Lifespan lifespan;
		Array<std::string> notable_works;
		std::string biography;
		Novel(std::string name, attrs::FullName author,
		      attrs::Lifespan author_lifespan, Array<std::string> notable_works,
		      std::string biography);
		~Novel();
		void about_author(std::ostream &out) const final;
	};
}