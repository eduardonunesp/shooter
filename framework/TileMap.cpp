#include "TileMap.h"
#include "TileSet.h"
#include "TileLayer.h"
#include "VideoManager.h"
#include "Logger.h"
#include <algorithm>

namespace Thing2D {
	TileMap::TileMap():
		video_manager(nullptr),
		height(0), width(0),
		tile_height(0), tile_width(0) {}

	void TileMap::init() {}

	void TileMap::update() {}

	void TileMap::render() {
		std::for_each(tile_layers.begin(), tile_layers.end(), [&](TileLayer* tile_layer) {
			for (int w = 0; w < tile_layer->width; w++) {
				for (int h = 0; h < tile_layer->height; h++) {
					int tile_id = tile_layer->tile_ids[w][h];

					if (tile_id == 0) {
						continue;
					}

					TileSet* tile_set = tile_set_by_id(tile_id);

					// texture id
					//tile_set->name



					//video_manager->render(tile_set->name)

					/*video_manager->render(texture_id, (int)position.x, (int)position.y, width, height, visible,
						curr_row, curr_col, angle, alpha, r, g, b, flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE,
						debug, colliders);*/
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

