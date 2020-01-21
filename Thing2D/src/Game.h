#pragma once

#include <string>
#include <map>

namespace Thing2D {
	class State;
	class VideoManager;
	class InputManager;

	class Game {
	public:
		Game(int screen_width, int screen_height, State* initial_state);
		virtual ~Game();

		// Lifecycle
		virtual void init();
		virtual void run();
		virtual void destroy();

		// State management
		void add_state(State *state, bool is_the_current_state);
		auto get_current_state(const std::string& state_id);
		void set_current_state(const std::string& state_id);

	protected:
		int screen_width;
		int screen_height;

		VideoManager* video_manager;
		InputManager* input_manager;

	private:
		bool running;
		State* initial_state;
		State* current_state;
		std::map<std::string, State*> states;
	};
}
