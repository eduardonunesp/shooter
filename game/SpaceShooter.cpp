#include "SpaceShooter.h"
#include "PlayState.h"

SpaceShooter::SpaceShooter() : 
	Game(640, 480),
	play_state(nullptr) {}

void SpaceShooter::init() {
	Game::init();
	video_manager->load_texture("./assets/plane.png", "plane");
	play_state = new PlayState();
	add_state("play_state", play_state, true);
}
