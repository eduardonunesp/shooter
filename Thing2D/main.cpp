#include "Thing2D.h"

using namespace Thing2D;

class PlayState : public State {};

int main() {
	PlayState playState;
	Game *game = new Game();
	game->AddState(&playState);
	game->Initialize();
	game->Run();
	game->Destroy();

	return 0;
}