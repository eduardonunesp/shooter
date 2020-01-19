#include "VideoManager.h"
#include <SDL_image.h>
#include "Logger.h"

namespace Thing2D {
	VideoManager* VideoManager::instance = NULL;

	void VideoManager::Init(int screenWidth, int screenHeight) {
		LOG("Initialize VideoManager");
		
		if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
			throw "Couldn't initialize SDL";
		}

		if (SDL_CreateWindowAndRenderer(screenWidth, screenHeight, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
			throw "Couldn't create window and renderer";
		}

		LOG("VideoManager Ready");
	}

	void VideoManager::Render()	{
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}

	void VideoManager::Destroy() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	SDL_Texture* VideoManager::LoadTexture(const std::string& filePath)	{
		SDL_Texture* newTexture = IMG_LoadTexture(renderer, filePath.c_str());

		if (!newTexture) {
			LOG("Failed to load texture " + filePath);
			return NULL;
		}

		textureMap[filePath] = newTexture;
		return newTexture;
	}
	
	void VideoManager::ClearTextureMap() {
		for (std::pair<std::string, SDL_Texture*> texture : textureMap) {
			SDL_DestroyTexture(texture.second);
		}

		textureMap.clear();
	}

	void VideoManager::ClearFromTextureMap(const std::string id) {
		textureMap.erase(id);
	}
}

