#include "Thing2D.h"

using namespace Thing2D;

int main() {
	Game *game = new Game();
	game->Initialize();
	game->Run();
	game->Destroy();

	return 0;
}