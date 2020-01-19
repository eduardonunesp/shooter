#include "Game.h"
#include "InputManager.h"
#include "VideoManager.h"
#include "State.h"

namespace Thing2D {
	const int FPS = 60;
	const int DELAY_TIME = 1000 / FPS;

	Game::Game(): videoManager(NULL), inputManager(NULL), currState(NULL) {
		running = false;
		frameTime = 0;
		frameStart = 0;
	}

	void Game::Init(int screenWidth, int screenHeight, State* initialState) {
		SDL_SetMainReady();
		videoManager = VideoManager::Instance();
		inputManager = InputManager::Instance();

		videoManager->Init(screenWidth, screenHeight);
		inputManager->Init();
		running = true;

		AddState(initialState);
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
			frameStart = SDL_GetTicks();

			inputManager->Read();

			if (inputManager->HasQuit()) {
				running = false;
			}

			if (currState) {
				currState->Update();
				currState->Draw();
			}

			videoManager->Render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME) {
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}

	void Game::Destroy() {
		inputManager->Destroy();
		videoManager->Destroy();
	}
}