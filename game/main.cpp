#define main SDL_main
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <Thing2D.h>
#include "SpaceShooter.h"

using namespace Thing2D;
using namespace SpaceShooter;

int main(int argc, char* args[]) {
#ifdef _DEBUG
		AllocConsole();
		freopen("conin$", "r", stdin);
		freopen("conout$", "w", stdout);
		freopen("conout$", "w", stderr);
		printf("Debugging Window:\n");
#endif

	SpaceShooterGame* space_shooter = new SpaceShooterGame();
	space_shooter->init();
	space_shooter->run();
	delete space_shooter;

	return 0;
}