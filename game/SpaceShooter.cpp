#include "SpaceShooter.h"
#include "PlayState.h"

namespace SpaceShooter {
	SpaceShooterGame::SpaceShooterGame() :
		Game(800, 600),
		play_state(nullptr) {}

	void SpaceShooterGame::init() {
		Game::init();
		video_manager->load_texture("./assets/plane.png", "plane");
		video_manager->load_texture("./assets/shot.png", "shot");
		play_state = new PlayState();
		add_state("play_state", play_state, true);
	}
}