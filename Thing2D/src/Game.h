#pragma once
#include <vector>

namespace Thing2D {
	class State;

	class Game {
	public:
		Game(int screen_width, int screen_height, State* initial_state);
		virtual ~Game();

		void init();
		void add_state(State *state);
		void set_current_state(int stateIdx);
		void run();
		void destroy();

	private:
		int screen_width;
		int screen_height;
		bool running;
		State* initial_state;
		State* current_state;
		std::vector<State*> states;
	};
}
