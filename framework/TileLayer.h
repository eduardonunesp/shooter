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
		friend class TileMapManager;
		friend class TileMap;

		std::string name;
		int width;
		int height;

		std::vector<std::vector<int>> tile_ids;
	};
}