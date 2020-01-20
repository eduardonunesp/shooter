#include "Game.h"
#include "InputManager.h"
#include "VideoManager.h"
#include "TimerManager.h"
#include "State.h"

namespace Thing2D {
	const int FPS = 60;
	const int DELAY_TIME = 1000 / FPS;

	Game::Game(): currState(NULL) {
		running = false;
	}

	void Game::init(int screenWidth, int screenHeight, State* initialState) {
		SDL_SetMainReady();
		VideoManager::get_instance()->init(screenWidth, screenHeight);
		InputManager::get_instance()->init();
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
		Uint32 frameStart = 0;
		Uint32 frameTime = 0;

		while (running) {
			frameStart = SDL_GetTicks();

			TimerManager::get_instance()->deltaTime = frameTime;
			InputManager::get_instance()->read();

			if (InputManager::get_instance()->has_quit()) {
				running = false;
			}

			VideoManager::get_instance()->clear();

			if (currState) {
				currState->update();
				currState->draw();
			}

			VideoManager::get_instance()->render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameTime < DELAY_TIME) {
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}

	void Game::destroy() {
		InputManager::get_instance()->destroy();
		VideoManager::get_instance()->destroy();
	}
}