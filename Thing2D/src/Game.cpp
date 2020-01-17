#include "Game.h"
#include "EventManager.h"
#include "VideoManager.h"

namespace Thing2D {
	void Game::Initialize()	{
		videoManager = new VideoManager();
		eventManager = new EventManager();

		videoManager->Init();
		eventManager->Init();
		running = true;
	}

	void Game::Run() {
		while (running) {
			eventManager->Read();

			if (eventManager->HasQuit()) {
				running = false;
			}

			videoManager->Render();
		}
	}

	void Game::Destroy() {
		eventManager->Destroy();
		videoManager->Destroy();
	}
}