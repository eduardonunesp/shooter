#pragma once

#include <SDL.h>
#include <vector>
#include <string>

namespace Thing2D {
	class VideoManager {
	public:
		void Init();
		void Render();
		void Destroy();
		inline SDL_Renderer* GetRenderer() { return renderer; }
		SDL_Texture* LoadTexture(const std::string& filePath);

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		std::vector<SDL_Texture*> textures;
	};
}
