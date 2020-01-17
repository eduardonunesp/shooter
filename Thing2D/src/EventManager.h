#pragma once

#include <SDL.h>

namespace Thing2D {
	class EventManager {
	public:
		bool Init();
		void Read();
		void Destroy();
		inline bool HasQuit() { return hasQuit; }

	private:
		bool hasQuit;
		SDL_Event event;
	};
}

