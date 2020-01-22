#pragma once

#include <Thing2D.h>

using namespace Thing2D;

namespace SpaceShooter {
	class Player : public Sprite {
	public:
		Player();

		void update() override;

	private:
		float speed;
	};
}