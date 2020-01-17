#pragma once

namespace Thing2D {
	class VideoManager;
	class EventManager;

	class Game {
	public:
		void Initialize();
		void Run();
		void Destroy();

	private:
		bool running;
		VideoManager* videoManager;
		EventManager* eventManager;
	};
}
