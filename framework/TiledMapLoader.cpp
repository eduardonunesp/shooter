#include "TiledMapLoader.h"
#include <zlib.h>
#include <algorithm>
#include <math.h>
#include "base64.h"
#include "TiledState.h"
#include "TileLayer.h"
#include "TileSet.h"
#include "Tile.h"
#include "Logger.h"
#include "VideoManager.h"

namespace Thing2D {
	void TiledMapLoader::init() {
		LOG("Initialize TileMap Manager");
		assets_path = "./assets/";
	}

	void TiledMapLoader::update() {
		std::for_each(tilemaps.begin(), tilemaps.end(), [](auto tilemap) {
			tilemap.second->update();
		});
	}

	void TiledMapLoader::render() {
		std::for_each(tilemaps.begin(), tilemaps.end(), [](auto tilemap) {
			tilemap.second->render();
		});
	}

	void TiledMapLoader::destroy() {}
	
	void TiledMapLoader::load_tmx_map(const std::string& file_path, const std::string& map_id) {
		LOG("Loading tile map " << file_path);

		TiXmlDocument levelDocument;
		if (!levelDocument.LoadFile(file_path.c_str())) {
			ERR("Error on loading tmx file");
			throw "Failed to load tmx fila map";
		}

		TiledState* new_tile_map = new TiledState();
		curr_tile_map = new_tile_map;
		tilemaps[map_id] = new_tile_map;
		curr_tile_map->video_manager = video_manager;

		TiXmlElement* pRoot = levelDocument.RootElement();
		LOG("Loading level:\n" << "Version: " << pRoot->Attribute("version"));
		LOG("Width:" << pRoot->Attribute("width") << " - Height:" << pRoot->Attribute("height"));
		LOG("Tile Width:" << pRoot->Attribute("tilewidth") << " - Tile Height:" << pRoot->Attribute("tileheight"));

		pRoot->Attribute("tilewidth", &new_tile_map->tile_width);
		pRoot->Attribute("tileheight", &new_tile_map->tile_height);
		pRoot->Attribute("width", &new_tile_map->cols);
		pRoot->Attribute("height", &new_tile_map->rows);

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
		curr_tile_map = nullptr;
	}

	void TiledMapLoader::parse_tilesets(TiXmlElement* tileset_root) {
		TileSet* new_tile_set = new TileSet();
		curr_tile_map->tile_sets.push_back(new_tile_set);

		const std::string texture_path = assets_path + tileset_root->FirstChildElement()->Attribute("source");
		LOG("adding texture " << texture_path << " with ID " << tileset_root->Attribute("name"));
		video_manager->load_texture(texture_path, tileset_root->Attribute("name"));

		tileset_root->FirstChildElement()->Attribute("width", &new_tile_set->width);
		tileset_root->FirstChildElement()->Attribute("height", &new_tile_set->height);
		tileset_root->Attribute("firstgid", &new_tile_set->first_grid_id);
		tileset_root->Attribute("tilewidth", &new_tile_set->tile_width);
		tileset_root->Attribute("tileheight", &new_tile_set->tile_height);
		tileset_root->Attribute("spacing", &new_tile_set->spacing);
		tileset_root->Attribute("margin", &new_tile_set->margin);
		new_tile_set->name = tileset_root->Attribute("name");
		new_tile_set->texture_id = tileset_root->Attribute("name");

		int rows = floor(new_tile_set->width / new_tile_set->tile_width);
		int cols = floor(new_tile_set->height / new_tile_set->tile_height);

		for (int y = 0; y < cols; y++) {
			for (int x = 0; x < rows; x++) {
				Tile* tile = new Tile();
				tile->col = y;
				tile->row = x;
				curr_tile_map->tiles.push_back(tile);
			}
		}
	}
	
	void TiledMapLoader::parse_properties(TiXmlElement* properties_root) {
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
	
	void TiledMapLoader::parse_layers(TiXmlElement* layer_root) {
		LOG("Parsing" << layer_root->Attribute("name"));

		TileLayer* new_tile_layer = new TileLayer(layer_root->Attribute("name"));
		new_tile_layer->cols = curr_tile_map->cols;
		new_tile_layer->rows = curr_tile_map->rows;

		curr_tile_map->tile_layers.push_back(new_tile_layer);

		std::vector<std::vector<int>> data;


		std::string decoded_ids;
		TiXmlElement* data_node = nullptr;

		for (TiXmlElement* e = layer_root->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
			if (e->Value() == std::string("properties")) {
				for (TiXmlElement* property = e->FirstChildElement(); property != NULL; property = property->NextSiblingElement()) {
					if (property->Value() == std::string("property")) {
						// TODO: Add to others props
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
			uLongf size_of_ids = curr_tile_map->cols * curr_tile_map->rows * sizeof(int);
			std::vector<int> ids(curr_tile_map->cols * curr_tile_map->rows);
			uncompress((Bytef*)&ids[0], &size_of_ids, (const Bytef*)decoded_ids.c_str(), decoded_ids.size());

			std::vector<int> layer_row(curr_tile_map->cols);

			for (int j = 0; j < curr_tile_map->rows; j++) {
				data.push_back(layer_row);
			}

			for (int rows = 0; rows < curr_tile_map->rows; rows++) {
				for (int cols = 0; cols < curr_tile_map->cols; cols++) {
					data[rows][cols] = ids[rows * curr_tile_map->cols + cols];
				}
			}

			new_tile_layer->tile_ids = data;

		}

		LOG("Parsed layer " << layer_root->Attribute("name"));
	}
}
