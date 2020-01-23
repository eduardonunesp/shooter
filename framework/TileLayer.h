#pragma once

#include <string>
#include <map>
#include "Layer.h"

namespace Thing2D {
	class TileLayer : public Layer {
	public:
		TileLayer(int tile_size, int map_width, int map_height);

	protected:
		int tile_size;
		int map_width;
		int map_height;

		std::map<std::string, std::string> string_prop;
		std::map<std::string, int> int_prop;
	};
}