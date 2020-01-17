#pragma once
#include <vector>

namespace Thing2D {
	class VideoManager;
	class InputManager;
	class State;

	class Game {
	public:
		Game();

		void Init(int screenWidth, int screenHeight, State *initialState);
		void AddState(State *state);
		void SetCurrentState(int stateIdx);
		void Run();
		void Destroy();

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
