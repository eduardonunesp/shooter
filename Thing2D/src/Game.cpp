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

	void Game::init(int screenWidth, int screenHeight, State* initialState) {
		SDL_SetMainReady();
		videoManager = VideoManager::get_instance();
		inputManager = InputManager::get_instance();

		videoManager->init(screenWidth, screenHeight);
		inputManager->init();
		running = true;

		add_state(initialState);
	}

	void Game::add_state(State* state) {
		states.push_back(state);

		if (states.size() == 1) {
			set_current_state(0);
		}
	}

	void Game::set_current_state(int stateIdx) {
		State* newState = states.at(stateIdx);

		if (currState) {
			State* oldState = currState;
			oldState->destroy();
			currState = NULL;
		}
		
		currState = newState;
		newState->init();
	}

	void Game::run() {
		while (running) {
			frameStart = SDL_GetTicks();

			inputManager->read();

			if (inputManager->has_quit()) {
				running = false;
			}

			if (currState) {
				currState->update();
				currState->draw();
			}

			videoManager->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME) {
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}

	void Game::destroy() {
		inputManager->destroy();
		videoManager->destroy();
	}
}