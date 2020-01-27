#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"
#include "Shot.h"

namespace Shooter {
	const float tlayer_scrool_speed = 2.0f;
	const float player_speed = 10.0f;

	PlayState::PlayState() :
		State(), map(nullptr) {}

	void PlayState::init() {
		State::init();
		Tiled::TiledLayer* tlayer = new Tiled::TiledLayer(0, -(map->height - 600), map);
		LOG(" MAP HEIGHT " << map->height);
		tlayer->set_label("tiled layer");
		tlayer->set_order(-1);
		add_layer(tlayer);
		audio_manager->play_music("music");

		add("player", new Player());
		//add("enemy", new Enemy());
		create_timer("shot_timer", 60);
	}

	void PlayState::update() {
		if (input_manager->is_key_up(SDL_SCANCODE_ESCAPE)) {
			game->halt();
		}

		Layer* tlayer = get_layer(0);
		tlayer->set_velocity(Vector::down() * tlayer_scrool_speed);

		GameObject* player = default_layer->get("player");
		player->set_velocity(Vector::zero());

		if (input_manager->is_key_down(SDL_SCANCODE_RIGHT) && player->get_position().x + player->get_width() < game->get_screen_width()) {
			player->add_velocity(Vector::right() * player_speed);
		}

		if (input_manager->is_key_down(SDL_SCANCODE_LEFT) && player->get_position().x > 0) {
			player->add_velocity(Vector::left() * player_speed);
		}

		if (input_manager->is_key_down(SDL_SCANCODE_DOWN) && (player->get_position().y + player->get_height()) < game->get_screen_height()) {
			player->add_velocity(Vector::down() * player_speed);
		}

		if (input_manager->is_key_down(SDL_SCANCODE_UP) && player->get_position().y > 0) {
			player->add_velocity(Vector::up() * player_speed);
		}

		for (auto enemy : default_layer->all_by_tag("enemy")) {
			if (player->overlaps(enemy)) {
				enemy->hurt(1);
			}

			for (auto shot : default_layer->all_by_tag("shot")) {
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

		if (input_manager->is_key_up(SDL_SCANCODE_SPACE) && get_timer("shot_timer")->ended()) {
			Shot* shot = new Shot(0, 0);
			const Vector& player_pos = player->get_position();
			shot->move(player_pos.x + 35, player_pos.y);
			shot->set_velocity(Vector::up() * 20.0f);
			add(shot);
			audio_manager->play_sound("boom");
			get_timer("shot_timer")->reset();
		}
		

		State::update();
	}
}