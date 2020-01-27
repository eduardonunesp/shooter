#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"
#include "Shot.h"

namespace Shooter {
	PlayState::PlayState() :
		State(), map(nullptr) {}

	void PlayState::init() {
		State::init();
		//add("player", new Player(this));
		//add("enemy", new Enemy());
		//create_timer("shot_timer", 60);

		Tiled::TiledLayer* tlayer = new Tiled::TiledLayer(map);
		add_layer(tlayer);
	}

	void PlayState::update() {
		if (input_manager->is_key_up(SDL_SCANCODE_ESCAPE)) {
			game->halt();
		}

		//GameObject* player = default_layer->get("player");
		//
		//for (auto enemy : default_layer->all_by_tag("enemy")) {
		//	if (player->overlaps(enemy)) {
		//		enemy->hurt(1);
		//	}

		//	for (auto shot : default_layer->all_by_tag("shot")) {
		//		if (shot->is_dead()) {
		//			continue;
		//		}

		//		if (shot->get_position().y < 0) {
		//			shot->kill();
		//		}

		//		if (shot->overlaps(enemy)) {
		//			shot->kill();
		//			enemy->hurt(1);
		//		}
		//	}
		//}

		//if (input_manager->is_key_up(SDL_SCANCODE_SPACE) && get_timer("shot_timer")->ended()) {
		//	Shot* shot = new Shot(0, 0);
		//	const Vector& player_pos = player->get_position();
		//	shot->move(player_pos.x + 35, player_pos.y);
		//	shot->set_velocity(Vector::up() * 20.0f);
		//	add(shot);
		//	audio_manager->play_sound("boom");
		//	get_timer("shot_timer")->reset();
		//}

		State::update();
	}
}