#pragma once

#include <SDL.h>

namespace Thing2D {
	class VideoManager {
	public:
		void Init();
		void Render();
		void Destroy();

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
	};
}
