#pragma once
#include <Thing2D.h>
#include <EntryPoint.h>

namespace Shooter {
	class TiledMapLoader;

	class ShooterGame : public Thing2D::Game {
	public:
		ShooterGame();
		void init();

	protected:
		TiledMapLoader* tiled_map_loader;
	};
}

Thing2D::Game * Thing2D::CreateGame() {
	return new Shooter::ShooterGame();
}