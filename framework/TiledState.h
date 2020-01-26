#pragma once
#include <vector>
#include <string>
#include "Props.h"
#include "State.h"

namespace Thing2D {
	class TileLayer;
	class TileSet;
	class Tile;
	class VideoManager;

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

		std::string orientation;
		int cols, rows;
		int tile_width, tile_height;

		TileSet* tile_set_by_id(int id);

		std::vector<TileSet*> tile_sets;
		std::vector<TileLayer*> tile_layers;
		std::vector<Tile*> tiles;
	};
}
