#include "TileMap.h"
#include "TileSet.h"
#include "TileLayer.h"
#include "VideoManager.h"
#include <algorithm>

namespace Thing2D {
	TileMap::TileMap():
		video_manager(nullptr),
		height(0), width(0),
		tile_height(0), tile_width(0) {}

	void TileMap::init() {}

	void TileMap::update() {}

	void TileMap::render() {
		std::for_each(tile_layers.begin(), tile_layers.end(), [](TileLayer* tile_layer) {
			
		});

		//(const std::string & texture_id, int x, int y, int width, int height, bool visible,
		//	int current_row, int current_col, double angle, int alpha, int r, int g, int b, SDL_RendererFlip flip,
		//	bool debug, std::vector<Collider*> debug_boxes)
	}

	void TileMap::destroy() {}
}

