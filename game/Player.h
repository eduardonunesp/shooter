#pragma once

#include <Thing2D.h>

using namespace Thing2D;

namespace SpaceShooter {
	class PlayState;
	class Player : public Sprite {
	public:
		Player(PlayState *state);

		void init() override;
		void update() override;

	private:
		float speed;
		PlayState* play_state;
	};
}