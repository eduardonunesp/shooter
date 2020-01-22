#include "Player.h"

namespace SpaceShooter {
	Player::Player() : Sprite("plane", 100, 100, 65, 65, 1, 3), speed(10.0f) {}

	void Player::init() {
		Sprite::init();


		add_animations("fly", 12, true, 3, 0, 1, 2);
		position.x = (game->get_screen_width() / 2) - width;
		
		debug = true;

		create_box(position.x, position.y, 20, 20, "left_wing_box");

		//rect.offset_x -= 10;
		
	}

	void Player::update() {
		velocity = Vector::zero();

		if (input_manager->is_key_down(SDL_SCANCODE_RIGHT) && position.x + boxes[0]->w < game->get_screen_width()) {
			velocity += Vector::right() * speed;
		}

		if (input_manager->is_key_down(SDL_SCANCODE_LEFT)) {
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