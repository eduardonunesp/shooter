#pragma once

#include <map>
#include <string>


namespace Thing2D {
	namespace Tiled {
		class Props {
		public:
			const std::string& get_string_prop(const std::string& prop_id) {
				return string_prop[prop_id];
			}

			const int get_int_prop(const std::string& prop_id) {
				return int_prop[prop_id];
			}

		protected:
			std::map<std::string, std::string> string_prop;
			std::map<std::string, int> int_prop;
		};
	}
}