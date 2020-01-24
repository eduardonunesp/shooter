#pragma once

#include <string>
#include <map>

namespace Thing2D {
	class TileMap;

	class TileMapManager {
	public:
		void init();

	protected:
		std::map<std::string, TileMap*> tilemaps;
	};
}