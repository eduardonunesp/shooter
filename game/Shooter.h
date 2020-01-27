#pragma once
#include <Thing2D/Thing2D.h>
#include <Thing2D/Tiled/Tiled.h>
#include <Thing2D/EntryPoint.h>

namespace Shooter {
	class ShooterGame : public Thing2D::Game {
	public:
		ShooterGame();
		void init();
	};
}

Thing2D::Game * Thing2D::CreateGame() {
	return new Shooter::ShooterGame();
}