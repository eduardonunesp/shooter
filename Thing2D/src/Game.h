#pragma once
#include <vector>

namespace Thing2D {
	class VideoManager;
	class EventManager;
	class State;

	class Game {
	public:
		void Initialize();
		void AddState(State *state);
		void SetCurrentState(int stateIdx);
		void Run();
		void Destroy();

	private:
		bool running;
		State* currState;
		std::vector<State*> states;
		VideoManager* videoManager;
		EventManager* eventManager;
	};
}
