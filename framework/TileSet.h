#pragma once

#include <string>
#include <map>

namespace Thing2D {
	class TileSet {
	public:
		int id;
		int tile_width;
		int tile_height;
		int spacing;
		int margin;
		int width;
		int height;
		int num_columns;
		std::string name;

		std::map<std::string, std::string> string_prop;
		std::map<std::string, int> int_prop;
	};
}
