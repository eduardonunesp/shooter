#pragma once

#include "Thing2D.h"

#if WIN && _DEBUG
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#endif


int main(int argc, char** argv) {
#if WIN && _DEBUG
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
	printf("Debugging Window:\n");
#endif

	

	auto game = Thing2D::CreateGame();
	game->init();
	game->run();
	delete game;

	return 0;
}