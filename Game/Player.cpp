#include "Player.h"
#include "Shot.h"
#include "PlayState.h"

namespace Shooter {
	Player::Player() :
		Sprite("plane", 100, 100, 65, 65, 1, 3) {}

	void Player::init() {
		Sprite::init();

		add_animations("fly", 12, true, 3, 0, 1, 2);
		position.x = ((int)game->get_screen_width() / 2) - width;
		position.y = 500;
		
		debug = true;

		Collider *box0 = get_collider(0);
		box0->offset_x = 8;
		box0->offset_y = 8;
		box0->w = 33;
		box0->h = 38;
	}

	void Player::update() {
		Sprite::update();
	}
}