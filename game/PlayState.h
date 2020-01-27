#pragma once

#include <Thing2D.h>

using namespace Thing2D;

namespace Shooter {
	class Player;
	class TiledMapLoader;

	class PlayState : public TiledState
	{
	public:
		PlayState(TiledMapLoader* tiled_map_loader);

		void init() override;
		void update() override;
	};
}