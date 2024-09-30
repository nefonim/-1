#pragma once

#include <ostream>
#include <string>

namespace attrs {
	struct FullName {
		std::string first, last, middle;
		friend std::ostream &operator<<(std::ostream &, const FullName &);
	};
}
