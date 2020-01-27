#pragma once

#include <string>
#include <map>
#include "Props.h"

namespace Thing2D {
	namespace Tiled {

		class TileSet : public Props {
		protected:
			friend class TiledState;
			friend class TiledMapLoader;

			// Tileset congs
			int first_grid_id;
			std::string name;
			std::string orientation;
			int tile_width, tile_height;

			// Texture confs
			int width, height;
			int spacing;
			int margin;
			std::string texture_id;
		};
	}
}