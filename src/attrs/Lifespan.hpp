#pragma once

#include <ostream>
#include <cstdint>

namespace attrs {
	using year_t = uint16_t;

	struct Lifespan {
		year_t born, died;
		friend std::ostream &operator<<(std::ostream &, const Lifespan &);
	};
}