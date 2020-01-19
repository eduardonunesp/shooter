#include "Thing2D.h"

using namespace Thing2D;

class PlayState : public State {
public:
	void Init() {
		LOG("ADDED");
		gb = new GameObject(10, 10, 16, 16);
		gb->LoadTexture("./assets/bot.png");
		gb->Move(20, 20);
		Add(gb);
	}

	void Update() {
		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_RIGHT)) {
			gb->Move(10, 0);
		}

		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_LEFT)) {
			gb->Move(-10, 0);
		}

		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_DOWN)) {
			gb->Move(0, 10);
		}

		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_UP)) {
			gb->Move(0, -10);
		}

		State::Update();
	}

	GameObject* gb;
};

int main() {
	PlayState playState;
	Game *game = new Game();
	game->Init(640, 480, &playState);
	game->Run();
	game->Destroy();

	return 0;
}