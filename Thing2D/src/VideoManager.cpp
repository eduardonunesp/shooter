#include "VideoManager.h"

namespace Thing2D {
	void VideoManager::Init() {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			throw "Couldn't initialize SDL";
		}

		if (SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
			throw "Couldn't create window and renderer";
		}
	}

	void VideoManager::Render()	{
	}

	void VideoManager::Destroy() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}

