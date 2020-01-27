#pragma once

#include <string>
#include <map>
#include <tinyxml.h>

namespace Thing2D {
	class TiledState;
	class VideoManager;

	class TiledMapLoader {
	public:
		TiledMapLoader(VideoManager* video_manager) :
			video_manager(video_manager), 
			curr_tile_map(nullptr) {}

		// Life cycle
		void init();
		void destroy();

		// Load map
		void load_tmx_map(const std::string& map_id, const std::string& file_path);

	protected:
		friend class Game;

		// Needed to load texture
		VideoManager* video_manager;

		void parse_tilesets(TiXmlElement* tileset_root);
		void parse_properties(TiXmlElement* properties_root);
		void parse_layers(TiXmlElement* layer_root);

		std::string assets_path;
		TiledState* curr_tile_map;
		std::map<std::string, TiledState*> tilemaps;
	};
}