#pragma once

#include "Props.h"

namespace Thing2D {
	namespace Tiled {
		class Tile : public Props {
		public:
			Tile(unsigned int id, unsigned int row, unsigned int col) :
				row(row), col(col) {}

			unsigned int id;
			unsigned int row;
			unsigned int col;
		};
	}
}
