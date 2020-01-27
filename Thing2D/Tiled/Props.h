#pragma once

#include <map>
#include <string>

namespace Thing2D {
	namespace Tiled {
		struct Props {
			std::map<std::string, std::string> string_prop;
			std::map<std::string, int> int_prop;
		};
	}
}