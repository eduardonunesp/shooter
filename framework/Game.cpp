#include "Game.h"
#include "InputManager.h"
#include "VideoManager.h"
#include "AudioManager.h"
#include "State.h"
#include "Logger.h"

namespace Thing2D {
	Game::Game(int screen_width, int screen_height) :
		screen_width(screen_width), screen_height(screen_height),
		video_manager(nullptr), input_manager(nullptr), audio_manager(nullptr),
		current_state(nullptr),
		running(false) {}

	Game::~Game() {
		LOG("Destroying game resources");
		destroy();
	}

	void Game::init() {
		LOG("Init Game");
		
		SDL_SetMainReady();
		
		video_manager = new VideoManager();
		video_manager->init(screen_width, screen_height);

		input_manager = new InputManager();
		input_manager->init();

		audio_manager = new AudioManager();
		audio_manager->init();

		running = true;

		LOG("Game initialized");
	}

	void Game::add_state(const std::string& state_id, State* state, bool is_the_current_state) {
		if (state) {
			LOG("Adding state id: " + state_id);

			states[state_id] = state;

			if (is_the_current_state) {
				set_current_state(state_id);
			}
		}
	}

	auto Game::get_state_by_id(const std::string& state_id) {
		return states[state_id];
	}

	auto Game::get_current_state() {
		return current_state;
	}

	void Game::set_current_state(const std::string& state_id) {
		State* new_state = states[state_id];

		if (new_state) {
			if (current_state) {
				State* old_state = current_state;
				old_state->destroy();
				current_state = nullptr;
			}

			current_state = new_state;
			current_state->game = this;
			current_state->video_manager = video_manager;
			current_state->input_manager = input_manager;
			current_state->audio_manager = audio_manager;

			LOG("Set current state: " + state_id);

			new_state->init();
		}
	}

	void Game::run() {
		const Uint32 fps = video_manager->get_refresh_rate();
		const Uint32 delay_time = 1000 / fps;

		Uint32 frame_start = 0;
		Uint32 frame_time = 0;

		LOG("Running the main loop " << running);

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

			if (frame_time < delay_time) {
				SDL_Delay((int)(delay_time - frame_time));
			}
		}
	}

	void Game::destroy() {
		LOG("Destroying Game");
		input_manager->destroy();
		video_manager->destroy();
	}
}
