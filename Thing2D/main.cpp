#include "Thing2D.h"

using namespace Thing2D;

class LifeBar : public Group {
public:
	LifeBar(): Group(5, 5) {
		for (int i = 0; i < 3; i++) {
			GameObject* cursor = new GameObject("cursor", (float)i*15, 0, 10, 10);
			add("cursor_" + std::to_string(i+1), cursor);
		}
	}

	void die() {
		if (count_visible() > 0) {
			GameObject* cursor = get("cursor_" + std::to_string(count_visible()));
			cursor->visible = false;
		}
	}
};

class Bullet : public Sprite {
public:
	Bullet(float speed, Vector direction, float x, float y) : Sprite("bot_bullet", x, y, 4, 4, 1, 5) {
		add_animations("shot", 0);
		add_animations("explode", 2, false, 5, 0, 1, 2, 3, 4);
		play("shot");
		velocity = direction * speed;
	}

	void update() {
		if (position.x >= 640 && visible) {
			velocity = Vector::zero();
			play("explode");
			visible = false;
			LOG("EXPLO");
		}

		Sprite::update();
	}
};

class PlayState : public State {
public:
	void init() {
		gb = new Sprite("bot", 10, 10, 16, 16);
		gb->move(20, 20);
		add(gb);

		lifeBar = new LifeBar();
		add(lifeBar);

		spaceman = new Sprite("spaceman", 200, 200, 8, 8, 4, 4);
		spaceman->add_animations("run", 12, true, 3, 1, 2, 3, 0);
		spaceman->add_animations("idle", 1, false, 1, 0);
		spaceman->play("idle");
		add(spaceman);
	}

	void update() {
		gb->velocity = Vector::zero();
		spaceman->velocity = Vector::zero();
		spaceman->play("idle");

		if (InputManager::get_instance()->is_key_down(SDL_SCANCODE_RIGHT) && spaceman->position.x < 620) {
			spaceman->velocity = Vector::right() * speed;
			spaceman->play("run");
			spaceman->flipped = false;
		}

		if (InputManager::get_instance()->is_key_down(SDL_SCANCODE_LEFT) && spaceman->position.x > 0) {
			spaceman->velocity = Vector::left() * speed;
			spaceman->play("run");
			spaceman->flipped = true;
		}

		//if (InputManager::get_instance()->is_key_down(SDL_SCANCODE_DOWN) && gb->position.y < 460) {
		//	gb->velocity = Vector::down() * speed;
		//}

		//if (InputManager::get_instance()->is_key_down(SDL_SCANCODE_UP) && gb->position.y > 0) {
		//	gb->velocity = Vector::up() * speed;
		//}

		if (InputManager::get_instance()->is_key_up(SDL_SCANCODE_SPACE)) {
			add(new Bullet(10.0f, Vector::right(), spaceman->position.x, spaceman->position.y));
		}

		State::update();
	}

	float speed = 2;
	LifeBar* lifeBar;
	Sprite* gb;
	Sprite* bullet;
	Sprite* spaceman;

	PlayState() : gb(NULL), lifeBar(NULL), bullet(NULL) {}
};

class MyGame : public Game {
public:
	MyGame() : Game(640, 480, 0) {
		add_state(&playState);
	}

	void init() {
		Game::init();
		load_texture("./assets/bot.png", "bot");
		load_texture("./assets/cursor.png", "cursor");
		load_texture("./assets/bot_bullet.png", "bot_bullet");
		load_texture("./assets/spaceman.png", "spaceman");
	}

	void load_texture(const std::string& path, const std::string& texture_id) {
		VideoManager::get_instance()->load_texture(path, texture_id);
	}

private:
	PlayState playState;
};


int main() {
	MyGame *game = new MyGame();
	game->init();
	game->run();
	game->destroy();

	return 0;
}