#pragma once

#include <Thing2D/Thing2D.h>

using namespace Thing2D;

namespace Shooter {
	class PlayState;
	class Player : public Sprite {
	public:
		Player();

		void init() override;
		void update() override;
	};
}