#pragma once
#include <vector>

namespace Thing2D {
	class TileLayer;
	class TileSet;

	class TileMap {
	public:
		TileMap();

		// Life cycle
		void init();
		void update();
		void render();
		void destroy();

	protected:
		std::vector<TileSet*> tile_sets;
		std::vector<TileLayer*> tile_layers;
	};
}
