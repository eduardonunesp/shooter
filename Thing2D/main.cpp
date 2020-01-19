#include "Thing2D.h"

using namespace Thing2D;

class PlayState : public State {
public:
	void init() {
		LOG("ADDED");
		gb = new GameObject(10, 10, 16, 16);
		gb->load_texture("./assets/bot.png");
		gb->move(20, 20);
		add(gb);
	}

	void update() {
		if (InputManager::Instance()->key_down(SDL_SCANCODE_RIGHT)) {
			gb->move(10, 0);
		}

		if (InputManager::Instance()->key_down(SDL_SCANCODE_LEFT)) {
			gb->move(-10, 0);
		}

		if (InputManager::Instance()->key_down(SDL_SCANCODE_DOWN)) {
			gb->move(0, 10);
		}

		if (InputManager::Instance()->key_down(SDL_SCANCODE_UP)) {
			gb->move(0, -10);
		}

		State::update();
	}

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