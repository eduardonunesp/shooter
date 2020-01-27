#pragma once
#include <vector>
#include <string>
#include "Props.h"

namespace Thing2D {
	class Collider;
	class VideoManager;

	namespace Tiled {
		class TileLayer;
		class TileSet;
		class Tile;
		class MapLoader;

		class State : public Props {
		public:
			State();

			// Life cycle
			void init();
			void update();
			void render();
			void destroy();

		protected:
			friend class MapLoader;

			MapLoader* tiled_map_loader;
			VideoManager* video_manager;

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
}