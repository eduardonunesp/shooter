#pragma once

#include <string>
#include <vector>
#include "Props.h"

namespace Thing2D {
	namespace Tiled {
		struct TileLayer : public Props {
			TileLayer(const std::string& name);

			std::string name;
			int cols, rows;
			std::vector<std::vector<int>> tile_ids;
		};
	}
}