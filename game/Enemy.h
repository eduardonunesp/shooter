#pragma once

#include <Thing2D.h>

using namespace Thing2D;

namespace Shooter {
	class Enemy : public Sprite {
	public:
		Enemy() : Sprite("plane", 10, 10, 65, 65, 1, 3) {
			tag = "enemy";
		}

		void init() override {
			Sprite::init();

			life = 3;
			add_animations("fly", 12, true, 3, 0, 1, 2);
			position.x = ((int)game->get_screen_width() / 2) - width;
			r = 255;
			g = 0;
			b = 0;
			debug = true;

			Collider* box0 = get_collider(0);
			box0->offset_x = 8;
			box0->offset_y = 8;
			box0->w = 33;
			box0->h = 38;
		}
	};
}