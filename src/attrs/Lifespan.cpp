#include "Lifespan.hpp"

using attrs::Lifespan;

namespace attrs {
	std::ostream &operator<<(std::ostream &out, const Lifespan &life) {
		return out << "(" << life.born << "-" << life.died << ")";
	}
}
