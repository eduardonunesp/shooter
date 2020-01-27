#pragma once

#include "Props.h"

namespace Thing2D {
	namespace Tiled {
		struct Tile : Props {
			unsigned int id;
			unsigned int row;
			unsigned int col;
		};
	}
}
