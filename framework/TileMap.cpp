#include "TileMap.h"
#include "TileSet.h"
#include "TileLayer.h"
#include "Tile.h"
#include "VideoManager.h"
#include "Logger.h"
#include <algorithm>

namespace Thing2D {
	TileMap::TileMap():
		video_manager(nullptr),
		rows(0), cols(0),
		tile_height(0), tile_width(0) {}

	void TileMap::init() {}

	void TileMap::update() {}

	void TileMap::render() {
		std::vector<Collider*> debug_boxes;

		std::for_each(tile_layers.begin(), tile_layers.end(), [&](TileLayer* tile_layer) {
			for (int layer_row = 0; layer_row < tile_layer->rows; layer_row++) {
				for (int layer_col = 0; layer_col < tile_layer->cols; layer_col++) {
					int tile_id = tile_layer->tile_ids[layer_row][layer_col];

					if (tile_id == 0) {
						continue;
					}

					TileSet* tile_set = tile_set_by_id(tile_id);

					if (tile_set) {
						tile_id--;
						
						Tile* tile = tiles[tile_id];

						int row = tile->row;
						int col = tile->col;
						
						video_manager->render(
							tile_set->name,
							layer_col * tile_height,
							layer_row * tile_width,
							tile_set->margin,
							tile_set->spacing,
							tile_width, tile_width, 
							true,
							row, col,
							0, 255, 255, 255, 255, SDL_FLIP_NONE,
							false, debug_boxes
						);
					} else {
						ERR("Error on instantiate tile set from tile set id: " << tile_set);
					}
				}
			}
		});
	}

	void TileMap::destroy() {}
	
	TileSet* TileMap::tile_set_by_id(int tile_id) {
		for (int i = 0; i < tile_sets.size(); i++) {
			if (i + 1 <= tile_sets.size() - 1) {
				if (tile_id >= tile_sets[i]->first_grid_id && tile_id < tile_sets[i + 1]->first_grid_id) {
					return tile_sets[i];
				}
			} else {
				return tile_sets[i];
			}
		}

		LOG("did not find tileset, returning empty tileset");
		return new TileSet();
	}
}

