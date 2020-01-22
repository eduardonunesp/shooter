#pragma once

#include <Thing2D.h>

using namespace Thing2D;

namespace SpaceShooter {
	class Player;

	class PlayState : public State {
	public:
		PlayState();

		void init() override;
		void update() override;

	private:
		Player* player;
	};
}