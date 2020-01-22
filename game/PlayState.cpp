#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"

namespace SpaceShooter {
	PlayState::PlayState() {}

	void PlayState::init() {
		State::init();
		player = new Player();
		add(player);
		add("enemy", new Enemy());
	}

	void PlayState::update() {
		if (input_manager->is_key_up(SDL_SCANCODE_ESCAPE)) {
			game->halt();
		}

		GameObject* go = get("enemy");
		
		if (player->overlaps(go)) {
			LOG("OVERRR LAPS");
		}

		State::update();
	}
}