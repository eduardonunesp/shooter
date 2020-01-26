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
	}

	void TileMap::destroy() {}
}

