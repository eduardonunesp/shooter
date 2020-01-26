#pragma once
#include <Thing2D.h>
#include <EntryPoint.h>

namespace Shooter {
	class ShooterGame : public Thing2D::Game {
	public:
		ShooterGame();
		void init();
	};
}

Thing2D::Game *Thing2D::CreateGame() {
	return new Shooter::ShooterGame();
}