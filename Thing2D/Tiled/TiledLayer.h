#pragma once

#include "../Layer.h"

namespace Thing2D {
	namespace Tiled {
		class Map;
		class TileSet;

		class TiledLayer : public Layer {
		public:
			TiledLayer(Map* map);

			void init() override;
			void render() override;

		protected:
			TileSet* tile_set_by_id(int tile_id);

			Map* map;
		};
	}
}