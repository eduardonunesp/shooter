#pragma once
#include <vector>

namespace Thing2D {
	class VideoManager;
	class InputManager;
	class State;

	class Game {
	public:
		Game();

		void init(int screenWidth, int screenHeight, State *initialState);
		void add_state(State *state);
		void set_current_state(int stateIdx);
		void run();
		void destroy();

	private:
		bool running;
		int frameStart;
		int frameTime;
		State* currState;
		std::vector<State*> states;
		VideoManager* videoManager;
		InputManager* inputManager;
	};
}
