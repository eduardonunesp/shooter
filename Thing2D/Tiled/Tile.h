#pragma once

#include "Props.h"
#include "../GameObject.h"

namespace Thing2D {
	namespace Tiled {
		class Tile : public GameObject, public Props {
		public:
			Tile(const std::string& texture_id, float x, float y, int width, int height) : 
				GameObject(texture_id, x, y, width, height), row(0), col(0) {}

			unsigned int row;
			unsigned int col;
		};
	}
}
