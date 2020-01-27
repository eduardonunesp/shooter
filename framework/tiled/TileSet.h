#pragma once

#include <string>
#include <map>
#include "Props.h"

namespace Thing2D {
	namespace Tiled {
		struct TileSet : Props {
			// Tileset confs
			int first_grid_id;
			int width, height;
			int tile_width, tile_height;
			int spacing;
			int margin;

			// Texture confs
			std::string texture_id;
		};
	}
}