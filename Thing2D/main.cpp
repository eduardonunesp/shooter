#include "Thing2D.h"

using namespace Thing2D;

class LifeBar : public Group {
public:
	LifeBar(): Group(5, 5) {
		for (int i = 0; i < 3; i++) {
			GameObject* cursor = new GameObject("./assets/cursor.png", i*15, 0, 10, 10);
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
		InputManager::get_instance()->can_repeat(SDL_SCANCODE_SPACE, false);
		gb = new GameObject("./assets/bot.png", 10, 10, 16, 16);
		gb->move(20, 20);

		lifeBar = new LifeBar();
		add(gb);
		add(lifeBar);
	}

	void update() {
		int x = 0;
		int y = 0;

		if (InputManager::get_instance()->is_key_down(SDL_SCANCODE_RIGHT)) {
			x = speed * TimerManager::get_instance()->deltaTime;
		}

		if (InputManager::get_instance()->is_key_down(SDL_SCANCODE_LEFT)) {
			x = -speed * TimerManager::get_instance()->deltaTime;
		}

		if (InputManager::get_instance()->is_key_down(SDL_SCANCODE_DOWN)) {
			y = speed * TimerManager::get_instance()->deltaTime;
		}

		if (InputManager::get_instance()->is_key_down(SDL_SCANCODE_UP)) {
			y = -speed * TimerManager::get_instance()->deltaTime;
		}

		if (gb->x >= 0 && gb->x <= 640) {
			gb->x += x;
		}

		if (InputManager::get_instance()->is_key_up(SDL_SCANCODE_SPACE)) {
			lifeBar->die();
		}

		State::update();
	}

	int speed = 10;
	LifeBar* lifeBar;
	GameObject* gb;
};

int main() {
	PlayState playState;
	Game *game = new Game();
	game->init(640, 480, &playState);
	game->run();
	game->destroy();

	return 0;
}