#pragma once
#include <vector>
#include <string>
#include "Props.h"

namespace Thing2D {
	class TileLayer;
	class TileSet;

	class TileMap : public Props {
	public:
		TileMap();

		// Life cycle
		void init();
		void update();
		void render();
		void destroy();

	protected:
		friend class TileMapManager;

		VideoManager* video_manager;

		std::string orientation;
		int width, height;
		int tile_width, tile_height;

		std::vector<TileSet*> tile_sets;
		std::vector<TileLayer*> tile_layers;
	};
}
