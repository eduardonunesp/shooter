#pragma once

#include <string>
#include <map>

namespace Thing2D {
	class VideoManager;
	class InputManager;
	class AudioManager;
	class State;

	class Game {
	public:
		Game(int screen_width, int screen_height);
		virtual ~Game();

		// Lifecycle
		virtual void init();
		virtual void run();
		virtual void destroy();

		// State management
		void add_state(const std::string& state_id, State* state, bool is_the_current_state = false);
		auto get_state_by_id(const std::string& state_id);
		void set_current_state(const std::string& state_id);
		State* get_current_state();

		// Window properties
		inline int get_screen_width() { return screen_width; }
		inline int get_screen_height() { return screen_height; }

		// Core properties
		inline unsigned int delta_time() { return frame_time; }
		
		inline void halt() {
			running = false;
		}

	protected:
		int screen_width;
		int screen_height;

		VideoManager* video_manager;
		InputManager* input_manager;
		AudioManager* audio_manager;

	private:
		bool running;
		unsigned int frame_time;
		State* current_state;
		std::map<std::string, State*> states;
	};
}
