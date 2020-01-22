#pragma once

#include <Thing2D.h>

using namespace Thing2D;

namespace SpaceShooter {
	class Shot : public Sprite {
	public:
		Shot(float x, float y) : Sprite("shot", x, y, 32, 32, 1, 1) {}

		void init() override {
			Sprite::init();
			add_idle_animation("idle");
			debug = true;
		}
	};
}