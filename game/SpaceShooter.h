#pragma once

#include <Thing2D.h>

using namespace Thing2D;

namespace SpaceShooter {
	class PlayState;

	class SpaceShooterGame : public Game {
	public:
		SpaceShooterGame();
		void init() override;

	private:
		PlayState* play_state;
	};
}
