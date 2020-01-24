#pragma once

#include <string>
#include <map>
#include "Props.h"

namespace Thing2D {
	class TileSet : public Props {
	protected:
		friend class TileMap;

		// Tileset congs
		int first_gid;
		int id;
		std::string name;
		std::string orientation;
		int grid_width, grid_height;

		// Texture confs
		int width, height;
		int spacing;
		int margin;
		std::string texture_id;
	};
}
