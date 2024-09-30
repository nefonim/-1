#pragma once

#include <ostream>
#include <string>

class Book {
	std::string name;
public:
	const std::string &get_name() const;
	virtual void about_author(std::ostream &out) const = 0;

	explicit Book(std::string name);
	virtual ~Book();
};
