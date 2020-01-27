#pragma once

#include "Props.h"

namespace Thing2D {
	namespace Tiled {
		struct Tile : Props {
			Tile(unsigned int id, unsigned int row, unsigned int col) :
				row(row), col(col) {}

			unsigned int id;
			unsigned int row;
			unsigned int col;
		};
	}
}
