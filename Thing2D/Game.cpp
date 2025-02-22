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
		running(false), 
		current_state(nullptr) {
#if defined(_DEBUG) 
		debug_mode = true;
#else
		debug_mode = false;
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef _WIN64
		curr_platform_os = PlatformOS::WIN_X64;
#else
		curr_platform_os = PlatformOS::WIN_386;
#endif
#elif __APPLE__
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
		curr_platform_os = PlatformOS::IOS_SIM;
#elif TARGET_OS_IPHONE
		curr_platform_os = PlatformOS::IOS_IPHONE;
#elif TARGET_OS_MAC
		curr_platform_os = PlatformOS::MACOS;
#else
#   error "Unknown Apple platform"
#endif
#elif __linux__
		curr_platform_os = PlatformOS::LINUX;
#else
#	error "Unknown compiler"
#endif
	}

	Game::~Game() {
		LOG("Destroying game resources");
		destroy();
	}

	void Game::init() {
		LOG("Init Game");
		
		SDL_SetMainReady();
		
		video_manager = new VideoManager();
		video_manager->game = this;
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
			LOG("Adding state id: " + state_id + " " << state);

			states[state_id] = state;

			if (is_the_current_state) {
				set_current_state(state_id);
			}
		}
	}

	auto Game::get_state_by_id(const std::string& state_id) {
		return states[state_id];
	}

	State* Game::get_current_state() {
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
		const Uint32 frame_target_time = 1000 / fps;

		Uint32 frame_start = 0;

		LOG("Running the main loop " << running);

		while (running) {
			while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_last_frame + frame_target_time));
			
			fdelta_time = (SDL_GetTicks() - ticks_last_frame) / 1000.0f;

			fdelta_time = (fdelta_time > 0.05f) ? 0.05f : fdelta_time;

			ticks_last_frame = SDL_GetTicks() - frame_start;

			input_manager->read();

			if (input_manager->has_quit()) {
				running = false;
			}

			video_manager->clear();

			if (current_state) {
				if (input_manager->has_focus()) {
					audio_manager->resume_all_playing();
					current_state->update();
				} else {
					audio_manager->stop_all_playing();
				}
				current_state->render();
			}

			video_manager->present();

			if (debug_mode) {
				SDL_SetWindowTitle(video_manager->window, std::to_string(fdelta_time).c_str());
			}
		}
	}

	void Game::destroy() {
		LOG("Destroying Game");
		input_manager->destroy();
		video_manager->destroy();
	}
}
