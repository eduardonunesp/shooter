#pragma once

#include <vector>
#include "../Layer.h"

namespace Thing2D {
	class Collider;

	namespace Tiled {
		struct Map;
		struct TileSet;

		class TiledLayer : public Layer {
		public:
			TiledLayer(float x, float y, Map* map);
			TiledLayer(Map* map);

			void init() override;
			void render() override;

		protected:
			TileSet* tile_set_by_id(int tile_id);

			Map* map;
			std::vector<Collider*> debug_boxes;
		};
	}
}