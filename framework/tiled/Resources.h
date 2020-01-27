#pragma once

#include <vector>

namespace Thing2D {
	namespace Tiled {
		class TileSet;
		class TileLayer;
		class Tile;

		struct TiledResources {
			std::vector<TileSet*> tile_sets;
			std::vector<TileLayer*> tile_layers;
			std::vector<Tile*> tiles;
		};
	}
}