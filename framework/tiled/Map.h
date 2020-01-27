#pragma once

#include <vector>
#include "Props.h"

namespace Thing2D {
	namespace Tiled {
		class TileSet;
		class TileLayer;
		class Tile;

		struct Map : Props {
			int tile_width, tile_height;
			int cols, rows;

			std::vector<TileSet*> tile_sets;
			std::vector<TileLayer*> tile_layers;
			std::vector<Tile*> tiles;
		};
	}
}