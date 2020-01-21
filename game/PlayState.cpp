#include "PlayState.h"
#include "Player.h"

PlayState::PlayState() {}

void PlayState::init() {
	State::init();
	player = new Player();
	add(player);
}

void PlayState::update() {
	if (input_manager->is_key_up(SDL_SCANCODE_ESCAPE)) {
		game->halt();
	}

	State::update();
}
