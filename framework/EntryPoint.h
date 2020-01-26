#pragma once

#ifdef WIN 
#define main SDL_main
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#endif
#include <Thing2D.h>
#include "Shooter.h"
#include "Thing2D.h"

int main(int argc, char** argv) {
#ifdef _DEBUG
	// AllocConsole();
	// freopen("conin$", "r", stdin);
	// freopen("conout$", "w", stdout);
	// freopen("conout$", "w", stderr);
	// printf("Debugging Window:\n");
#endif

	auto game = Thing2D::CreateGame();
	game->init();
	game->run();
	delete game;
}