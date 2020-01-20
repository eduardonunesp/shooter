#include "Thing2D.h"

using namespace Thing2D;

class LifeBar : public Group {
public:
	LifeBar(): Group(5, 5) {
		for (int i = 0; i < 3; i++) {
			GameObject* cursor = new GameObject("./assets/cursor.png", (float)i*15, 0, 10, 10);
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

class PlayState : public State {
public:
	void init() {
		gb = new GameObject("./assets/bot.png", 10, 10, 16, 16);
		gb->move(20, 20);

		lifeBar = new LifeBar();
		add(gb);
		add(lifeBar);
	}

	void update() {
		gb->velocity = Vector::zero();

		if (InputManager::get_instance()->is_key_down(SDL_SCANCODE_RIGHT) && gb->position.x < 620) {
			gb->velocity = Vector::right() * speed;
		}

		if (InputManager::get_instance()->is_key_down(SDL_SCANCODE_LEFT) && gb->position.x > 0) {
			gb->velocity = Vector::left() * speed;
		}

		if (InputManager::get_instance()->is_key_down(SDL_SCANCODE_DOWN) && gb->position.y < 460) {
			gb->velocity = Vector::down() * speed;
		}

		if (InputManager::get_instance()->is_key_down(SDL_SCANCODE_UP) && gb->position.y > 0) {
			gb->velocity = Vector::up() * speed;
		}

		if (InputManager::get_instance()->is_key_up(SDL_SCANCODE_SPACE)) {
			lifeBar->die();
		}

		State::update();
	}

	float speed = 10;
	LifeBar* lifeBar;
	GameObject* gb;

	PlayState() : gb(NULL), lifeBar(NULL) {}
};

class MyGame : public Game {
public:
	MyGame() : Game(640, 480, 0) {
		add_state(&playState);
	}

	void init() {
		Game::init();
		VideoManager::get_instance()->load_texture("./assets/bot.png");
		VideoManager::get_instance()->load_texture("./assets/cursor.png");
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