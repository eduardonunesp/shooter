#define main SDL_main
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <Thing2D.h>
#include "SpaceShooter.h"

using namespace Thing2D;

int main(int argc, char* args[]) {
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
	printf("Debugging Window:\n");

	SpaceShooter* space_shooter = new SpaceShooter();
	space_shooter->init();
	space_shooter->run();
	delete space_shooter;

	return 0;
}