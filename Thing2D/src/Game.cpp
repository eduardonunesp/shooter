#include "Game.h"
#include "EventManager.h"
#include "VideoManager.h"
#include "State.h"

namespace Thing2D {
	void Game::Initialize()	{
		videoManager = new VideoManager();
		eventManager = new EventManager();

		videoManager->Init();
		eventManager->Init();
		running = true;
	}

	void Game::AddState(State* state) {
		states.push_back(state);

		if (states.size() == 1) {
			SetCurrentState(0);
		}
	}

	void Game::SetCurrentState(int stateIdx) {
		State* newState = states.at(stateIdx);

		if (currState) {
			State* oldState = currState;
			oldState->Destroy();
			currState = NULL;
		}
		
		currState = newState;
		newState->Init();
	}

	void Game::Run() {
		while (running) {
			eventManager->Read();

			if (eventManager->HasQuit()) {
				running = false;
			}

			if (!currState) {
				throw "Current scene not set";
			}

			videoManager->Render();
		}
	}

	void Game::Destroy() {
		eventManager->Destroy();
		videoManager->Destroy();
	}
}