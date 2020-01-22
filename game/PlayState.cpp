#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"

namespace SpaceShooter {
	PlayState::PlayState() {}

	void PlayState::init() {
		State::init();
		add("player", new Player());
		add("enemy", new Enemy());
	}

	void PlayState::update() {
		if (input_manager->is_key_up(SDL_SCANCODE_ESCAPE)) {
			game->halt();
		}

		GameObject* go = get("enemy");
		GameObject* player = get("player");
		
		if (player->overlaps(go)) {
			kill(go);
		}

		State::update();
	}
}