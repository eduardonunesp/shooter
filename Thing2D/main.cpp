#include "Thing2D.h"

using namespace Thing2D;

class PlayState : public State {
	void Init() {
		LOG("ADDED");
		GameObject* gb = new GameObject(videoManager);
		gb->LoadTexture("./assets/bot.png");
		gb->Move(20, 20);
		Add(gb);
	}
};

int main() {
	PlayState playState;
	Game *game = new Game();
	game->Initialize();
	game->AddState(&playState);
	game->Run();
	game->Destroy();

	return 0;
}