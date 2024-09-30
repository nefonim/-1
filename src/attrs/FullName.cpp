#include "FullName.hpp"

using attrs::FullName;

namespace attrs {
	std::ostream &operator<<(std::ostream &out, const FullName &name) {
		return out << name.first << " " << name.last;
	}
}
