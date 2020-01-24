#include "TileMapManager.h"
#include <zlib.h>
#include <algorithm>
#include "base64.h"
#include "TileMap.h"
#include "TileLayer.h"
#include "TileSet.h"
#include "Logger.h"
#include "VideoManager.h"

namespace Thing2D {
	void TileMapManager::init() {
		LOG("Initialize TileMap Manager");
		assets_path = "./assets/";
	}

	void TileMapManager::update() {
		std::for_each(tilemaps.begin(), tilemaps.end(), [](auto tilemap) {
			tilemap.second->update();
		});
	}

	void TileMapManager::render() {
		std::for_each(tilemaps.begin(), tilemaps.end(), [](auto tilemap) {
			tilemap.second->render();
		});
	}

	void TileMapManager::destroy() {}
	
	void TileMapManager::load_tmx_map(const std::string& file_path, const std::string& map_id) {
		LOG("Loading tile map " << file_path);

		TiXmlDocument levelDocument;
		if (!levelDocument.LoadFile(file_path.c_str())) {
			ERR("Error on loading tmx file");
			throw "Failed to load tmx fila map";
		}

		TileMap* new_tile_map = new TileMap();
		tilemaps[map_id] = new_tile_map;
		curr_tile_map = new_tile_map;
		curr_tile_map->video_manager = video_manager;

		TiXmlElement* pRoot = levelDocument.RootElement();
		LOG("Loading level:\n" << "Version: " << pRoot->Attribute("version"));
		LOG("Width:" << pRoot->Attribute("width") << " - Height:" << pRoot->Attribute("height"));
		LOG("Tile Width:" << pRoot->Attribute("tilewidth") << " - Tile Height:" << pRoot->Attribute("tileheight"));

		pRoot->Attribute("tilewidth", &new_tile_map->tile_width);
		pRoot->Attribute("tileheight", &new_tile_map->tile_height);
		pRoot->Attribute("width", &new_tile_map->width);
		pRoot->Attribute("height", &new_tile_map->height);

		TiXmlElement* pProperties = pRoot->FirstChildElement();

		for (TiXmlElement* e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
			if (e->Value() == std::string("property")) {
				parse_properties(e);
			}
		}

		for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
			if (e->Value() == std::string("tileset")) {
				parse_tilesets(e);
			}
		}

		// parse any object layers
		for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
			if (e->Value() == std::string("layer")) {
				parse_layers(e);
			}
		}

		curr_tile_map->init();
	}

	void TileMapManager::parse_tilesets(TiXmlElement* tileset_root) {
		TileSet* new_tile_set = new TileSet();
		curr_tile_map->tile_sets.push_back(new_tile_set);

		const std::string texture_path = assets_path + tileset_root->FirstChildElement()->Attribute("source");
		LOG("adding texture " << texture_path << " with ID " << tileset_root->Attribute("name"));
		video_manager->load_texture(texture_path, tileset_root->Attribute("name"));

		tileset_root->FirstChildElement()->Attribute("width", &new_tile_set->width);
		tileset_root->FirstChildElement()->Attribute("height", &new_tile_set->height);
		tileset_root->Attribute("firstgid", &new_tile_set->first_gid);
		tileset_root->Attribute("tilewidth", &new_tile_set->tile_width);
		tileset_root->Attribute("tileheight", &new_tile_set->tile_height);
		tileset_root->Attribute("spacing", &new_tile_set->spacing);
		tileset_root->Attribute("margin", &new_tile_set->margin);
		new_tile_set->name = tileset_root->Attribute("name");
		new_tile_set->texture_id = tileset_root->Attribute("name");
	}
	
	void TileMapManager::parse_properties(TiXmlElement* properties_root) {
		const char* type = properties_root->Attribute("type");
		LOG("Property " << properties_root->Attribute("value") << " type " << (type ? type : "string") << " Name " << properties_root->Attribute("name"));

		if (type) {
			curr_tile_map->string_prop[properties_root->Attribute("name")] = std::string(properties_root->Attribute("value"));
		} else {
			int v;
			properties_root->Attribute("value", &v);
			curr_tile_map->int_prop[properties_root->Attribute("name")] = v;
		}
	}
	
	void TileMapManager::parse_layers(TiXmlElement* layer_root) {
		LOG("Parsing" << layer_root->Attribute("name"));

		TileLayer* new_tile_layer = new TileLayer(layer_root->Attribute("name"));
		new_tile_layer->width = curr_tile_map->width;
		new_tile_layer->height = curr_tile_map->height;

		curr_tile_map->tile_layers.push_back(new_tile_layer);

		std::vector<std::vector<int>> data;


		std::string decoded_ids;
		TiXmlElement* data_node = nullptr;

		for (TiXmlElement* e = layer_root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
			if (e->Value() == std::string("properties")) {
				for (TiXmlElement* property = e->FirstChildElement(); property != NULL; property = property->NextSiblingElement()) {
					if (property->Value() == std::string("property")) {

					}
				}
			}

			if (e->Value() == std::string("data")) {
				data_node = e;
			}
		}

		if (data_node != nullptr) {
			for (TiXmlNode* e = data_node->FirstChild(); e != NULL; e = e->NextSibling()) {
				TiXmlText* text = e->ToText();
				std::string t = text->Value();
				decoded_ids = base64_decode(t);
			}

			// uncompress zlib compression
			uLongf size_of_ids = curr_tile_map->width * curr_tile_map->height * sizeof(int);
			std::vector<int> ids(curr_tile_map->width * curr_tile_map->height);
			uncompress((Bytef*)&ids[0], &size_of_ids, (const Bytef*)decoded_ids.c_str(), decoded_ids.size());

			std::vector<int> layer_row(curr_tile_map->width);

			for (int j = 0; j < curr_tile_map->height; j++) {
				data.push_back(layer_row);
			}

			for (int rows = 0; rows < curr_tile_map->height; rows++) {
				for (int cols = 0; cols < curr_tile_map->width; cols++) {
					data[rows][cols] = ids[rows * curr_tile_map->width + cols];
				}
			}

			new_tile_layer->tile_ids = data;

		}

		curr_tile_map = nullptr;
		LOG("Parsed layer " << layer_root->Attribute("name"));
	}
}
