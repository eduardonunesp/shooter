#pragma once

#include <string>
#include <map>
#include <tinyxml.h>

namespace Thing2D {
	class VideoManager;

	namespace Tiled {
		class Map;

		class MapLoader {
		public:
			MapLoader(VideoManager* video_manager);

			// Life cycle
			void destroy();

			// Get
			Map* get_map(const std::string& map_id) { return maps[map_id]; }

			// Load map
			void load_tmx_map(const std::string& file_path, const std::string& map_id);

		protected:
			// Needed to load texture
			VideoManager* video_manager;

			void parse_tilesets(TiXmlElement* tileset_root);
			void parse_properties(TiXmlElement* properties_root);
			void parse_layers(TiXmlElement* layer_root);

			std::string assets_path;
			Map* curr_map;
			std::map<std::string, Map*> maps;
		};
	}
}