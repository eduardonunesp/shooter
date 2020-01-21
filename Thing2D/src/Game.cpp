#include "Game.h"
#include "InputManager.h"
#include "VideoManager.h"
#include "State.h"

namespace Thing2D {
	const int FPS = 60;
	const int DELAY_TIME = 1000 / FPS;

	Game::Game(int screen_width, int screen_height, State* initial_state) :
		screen_width(screen_width),
		screen_height(screen_height),
		video_manager(NULL),
		input_manager(NULL),
		initial_state(initial_state),
		current_state(NULL),
		running(false) {}

	Game::~Game() {
		destroy();
	}

	void Game::init() {
		SDL_SetMainReady();
		
		video_manager = new VideoManager();
		video_manager->init(screen_width, screen_height);

		input_manager = new InputManager();
		input_manager->init();

		running = true;
		add_state(initial_state, true);
	}

	void Game::add_state(State* state, bool is_the_current_state) {
		if (state) {
			states[state->state_id()] = state;

			if (is_the_current_state) {
				set_current_state(state->state_id());
			}
		}
	}

	auto Game::get_current_state(const std::string& state_id) {
		return states[state_id];
	}

	void Game::set_current_state(const std::string& state_id) {
		State* new_state = states[state_id];

		if (new_state) {
			if (current_state) {
				State* old_state = current_state;
				old_state->destroy();
				current_state = NULL;
			}

			current_state = new_state;
			new_state->init();
		}
	}

	void Game::run() {
		Uint32 frame_start = 0;
		Uint32 frame_time = 0;

		while (running) {
			frame_start = SDL_GetTicks();

			input_manager->read();

			if (input_manager->has_quit()) {
				running = false;
			}

			video_manager->clear();

			if (current_state) {
				current_state->update();
				current_state->draw();
			}

			video_manager->render();

			frame_time = SDL_GetTicks() - frame_start;

			if (frame_time < DELAY_TIME) {
				SDL_Delay((int)(DELAY_TIME - frame_time));
			}
		}
	}

	void Game::destroy() {
		input_manager->destroy();
		video_manager->destroy();
	}
}