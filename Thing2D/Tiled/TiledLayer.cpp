#include <algorithm>
#include "TiledLayer.h"
#include "Map.h"
#include "TileSet.h"
#include "Tile.h"
#include "../VideoManager.h"
#include "../Game.h"
#include "TileLayer.h"
#include "../Logger.h"

namespace Thing2D {
	namespace Tiled {
		TiledLayer::TiledLayer(Map *map) :
			TiledLayer(0, 0, map) {}

		TiledLayer::TiledLayer(int x, int y, Map* map) :
			Layer(x, y), map(map) {}

		void TiledLayer::init() {}
		
		void TiledLayer::render() {
			std::for_each(map->tile_layers.begin(), map->tile_layers.end(), [&](TileLayer* tile_layer) {
				for (int layer_row = 0; layer_row < tile_layer->rows; layer_row++) {
					for (int layer_col = 0; layer_col < tile_layer->cols; layer_col++) {
						int tile_id = tile_layer->tile_ids[layer_row][layer_col];

						if (tile_id == 0) {
							continue;
						}

						TileSet* tile_set = tile_set_by_id(tile_id);

						if (tile_set) {
							tile_id--;

							Tile* tile = map->tiles[tile_id];

							int row = tile->row;
							int col = tile->col;

							if (
								(((layer_row * map->tile_height) + map->tile_height + position.y) < 0) ||
								(((layer_row * map->tile_height) + map->tile_height + position.y) > game->get_screen_height() + map->tile_height) ||
								(((layer_col * map->tile_width) + map->tile_width + position.x) < 0) ||
								(((layer_col * map->tile_width) + map->tile_width + position.x) > game->get_screen_width() + map->tile_width)
							) {
								// Do not call draw off screen
								continue;
							}

							video_manager->render(
								tile_set->texture_id,
								(layer_col * map->tile_width) + position.x,
								(layer_row * map->tile_height) + position.y,
								tile_set->margin,
								tile_set->spacing,
								map->tile_width, map->tile_width,
								true,
								col, row,
								0, 255, 255, 255, 255, SDL_FLIP_NONE,
								false, debug_boxes
							);
						} else {
							ERR("Error on instantiate tile set from tile set id: " << tile_set);
						}
					}
				}
			});

			Layer::render();
		}

		TileSet* TiledLayer::tile_set_by_id(int tile_id) {
			for (int i = 0; i < map->tile_sets.size(); i++) {
				if (i + 1 <= map->tile_sets.size() - 1) {
					if (tile_id >= map->tile_sets[i]->first_grid_id && tile_id < map->tile_sets[i + 1]->first_grid_id) {
						return map->tile_sets[i];
					}
				} else {
					return map->tile_sets[i];
				}
			}

			LOG("did not find tileset, returning empty tileset");
			return new TileSet();
		}
	}
}