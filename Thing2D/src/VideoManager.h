#pragma once

#include <SDL.h>
#include <string>
#include <map>

namespace Thing2D {
	class VideoManager {
	public:
		static VideoManager* Instance() {
			if (!instance) {
				instance = new VideoManager();
			}

			return instance;
		}

		void Init(int screenWidth, int screenHeight);
		void Render();
		void Destroy();
		inline SDL_Renderer* GetRenderer() { return renderer; }
		SDL_Texture* LoadTexture(const std::string& filePath);
		void ClearTextureMap();
		void ClearFromTextureMap(const std::string textureId);

	private:
		VideoManager() : window(NULL), renderer(NULL) {}
		~VideoManager() { Destroy(); }

		SDL_Window* window;
		SDL_Renderer* renderer;
		std::map<std::string, SDL_Texture*> textureMap;
		static VideoManager* instance;
	};
}
