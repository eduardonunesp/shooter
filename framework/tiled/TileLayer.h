#pragma once

#include <string>
#include <vector>
#include "Layer.h"
#include "Props.h"

namespace Thing2D {
	class TileLayer: public Props {
	public:
		TileLayer(const std::string &name);

	protected:
		friend class TiledMapLoader;
		friend class TiledState;

		std::string name;
		int cols;
		int rows;

		std::vector<std::vector<int>> tile_ids;
	};
}