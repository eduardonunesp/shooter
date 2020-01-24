#include "Player.h"
#include "Shot.h"
#include "PlayState.h"

namespace SpaceShooter {
	Player::Player(PlayState *state) : Sprite("plane", 100, 100, 65, 65, 1, 3), speed(10.0f), play_state(state) {}

	void Player::init() {
		Sprite::init();

		add_animations("fly", 12, true, 3, 0, 1, 2);
		position.x = ((int)game->get_screen_width() / 2) - width;
		
		debug = true;

		Collider *box0 = get_collider(0);
		box0->offset_x = 8;
		box0->offset_y = 8;
		box0->w = 33;
		box0->h = 38;
	}

	void Player::update() {
		velocity = Vector::zero();

		if (input_manager->is_key_down(SDL_SCANCODE_RIGHT) && position.x + width < game->get_screen_width()) {
			velocity += Vector::right() * speed;
		}

		if (input_manager->is_key_down(SDL_SCANCODE_LEFT) && position.x > 0) {
			velocity += Vector::left() * speed;
		}

		if (input_manager->is_key_down(SDL_SCANCODE_DOWN)) {
			velocity += Vector::down() * speed;
		}

		if (input_manager->is_key_down(SDL_SCANCODE_UP)) {
			velocity += Vector::up() * speed;
		}

		Sprite::update();
	}
}