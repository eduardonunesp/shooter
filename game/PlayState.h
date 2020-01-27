#pragma once

#include <Thing2D/Thing2D.h>
#include <Thing2D/Tiled/Tiled.h>

using namespace Thing2D;

class Map;

namespace Shooter {
	class Player;

	class PlayState : public Thing2D::State
	{
	public:
		PlayState();

		void init() override;
		void update() override;

		Tiled::Map* map;
	};
}