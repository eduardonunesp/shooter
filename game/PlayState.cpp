#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"
#include "Shot.h"

namespace SpaceShooter {
	PlayState::PlayState() {}

	void PlayState::init() {
		State::init();
		add("player", new Player(this));
		add("enemy", new Enemy());
	}

	void PlayState::update() {
		if (input_manager->is_key_up(SDL_SCANCODE_ESCAPE)) {
			game->halt();
		}

		GameObject* player = get("player");
		
		for (auto enemy : all_by_tag("enemy")) {
			if (player->overlaps(enemy)) {
				enemy->hurt(1);
			}

			for (auto shot : all_by_tag("shot")) {
				if (shot->is_dead()) {
					continue;
				}

				if (shot->get_position().y < 0) {
					shot->kill();
				}

				if (shot->overlaps(enemy)) {
					shot->kill();
					enemy->hurt(1);
				}
			}
		}

		if (input_manager->is_key_up(SDL_SCANCODE_SPACE)) {
			Shot* shot = new Shot(position.x, position.y);
			const Vector& playerPos = player->get_position();
			shot->move(playerPos.x + 35, playerPos.y);
			shot->set_velocity(Vector::up() * 20.0f);
			add(shot);
			LOG("GET CURRENT STATE " << game->get_current_state());
		}

		State::update();
	}
}