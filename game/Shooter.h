#pragma once
#include <Thing2D.h>
#include <EntryPoint.h>

using namespace Thing2D;

namespace Shooter {
	class TiledMapLoader;

	class ShooterGame : public Game {
	public:
		ShooterGame();
		void init();

	protected:
		TiledMapLoader* tiled_map_loader;
	};
}

Game *CreateGame() {
	return new Shooter::ShooterGame();
}