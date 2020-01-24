#pragma once

#include <string>
#include <map>
#include <tinyxml.h>

namespace Thing2D {
	class TileMap;
	class VideoManager;

	class TileMapManager {
	public:
		// Life cycle
		void init();
		void update();
		void render();
		void destroy();

		// Load map
		void load_tmx_map(const std::string& map_id, const std::string& file_path);

	protected:
		friend class Game;

		VideoManager* video_manager;

		void parse_tilesets(TiXmlElement* tileset_root);
		void parse_properties(TiXmlElement* properties_root);
		void parse_layers(TiXmlElement* layer_root);

		std::string assets_path;
		TileMap* curr_tile_map;
		std::map<std::string, TileMap*> tilemaps;
	};
}