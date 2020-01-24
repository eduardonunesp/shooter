#pragma once

#include <string>
#include <map>
#include "Props.h"

namespace Thing2D {
	class TileSet : public Props {
	protected:
		friend class TileMap;

		enum class Orientation {
			ORIENTATION_ORTHOGANAL,
			ORIENTATION_ISOMETRIC
		};

		// Tileset congs
		int id;
		std::string name;
		Orientation orientation;
		int grid_width, grid_height;

		// Texture confs
		int width, height;
		int spacing;
		int margin;
		std::string texture_id;
	};
}
