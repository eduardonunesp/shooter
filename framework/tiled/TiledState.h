#pragma once
#include <vector>
#include <string>
#include "Props.h"
#include "State.h"

namespace Thing2D {
	class Collider;
	class TileLayer;
	class TileSet;
	class Tile;
	class TiledMapLoader;

	class TiledState : public State, public Props {
	public:
		TiledState();

		// Life cycle
		void init() override;
		void update() override;
		void render() override;
		void destroy() override;

	protected:
		friend class TiledMapLoader;

		TiledMapLoader* tiled_map_loader;

		std::string orientation;
		int cols, rows;
		int tile_width, tile_height;

		TileSet* tile_set_by_id(int id);

		std::vector<Collider*> debug_boxes;
		std::vector<TileSet*> tile_sets;
		std::vector<TileLayer*> tile_layers;
		std::vector<Tile*> tiles;
	};
}
