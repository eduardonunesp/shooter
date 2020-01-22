#pragma once

#include <Thing2D.h>

using namespace Thing2D;

namespace SpaceShooter {
	class Enemy : public Sprite {
	public:
		Enemy() : Sprite("plane", 10, 10, 65, 65, 1, 3) {}

		void init() override {
			add_animations("fly", 12, true, 3, 0, 1, 2);
			position.x = (game->get_screen_width() / 2) - width;
			r = 255;
			g = 0;
			b = 0;
			debug = true;
		}
	};
}