#include "SpaceShooter.h"
#include "PlayState.h"

void SpaceShooter::init() {
	Game::init();
	play_state = new PlayState();
	add_state("play_state", play_state, true);
}
