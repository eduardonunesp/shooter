#pragma once

#include <string>
#include <vector>
#include "Layer.h"
#include "Props.h"

namespace Thing2D {
	namespace Tiled {

		class TileLayer : public Props {
		public:
			TileLayer(const std::string& name);

		protected:
			friend class MapLoader;
			friend class State;

			std::string name;
			int cols;
			int rows;

			std::vector<std::vector<int>> tile_ids;
		};
	}
}