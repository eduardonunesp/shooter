#pragma once

#include "Props.h"

namespace Thing2D {
	namespace Tiled {
		class Tile : public Props {
		public:
			int id;
			int row;
			int col;
		};
	}
}
