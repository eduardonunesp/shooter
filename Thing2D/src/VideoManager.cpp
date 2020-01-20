#include "VideoManager.h"
#include <SDL_image.h>
#include "Logger.h"

namespace Thing2D {
	VideoManager* VideoManager::instance = NULL;

	void VideoManager::init(int screen_width, int screen_height) {
		LOG("Initialize VideoManager");
		
		if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
			throw "Couldn't initialize SDL";
		}

		int flags = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL;

		if (SDL_CreateWindowAndRenderer(screen_width, screen_height, flags, &window, &renderer)) {
			throw "Couldn't create window and renderer";
		}

		int w, h;
		SDL_GetWindowSize(window, &w, &h);

		LOG("VideoManager Ready " + std::to_string(w) + ":" + std::to_string(h));
	}

	void VideoManager::draw(const std::string& texture_id, int x, int y, int width, int height, SDL_RendererFlip flip) {
		SDL_Rect srcRect;
		SDL_Rect destRect;

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = destRect.w = width;
		srcRect.h = destRect.h = height;
		destRect.x = x;
		destRect.y = y;

		SDL_RenderCopyEx(renderer, texture_map[texture_id], &srcRect, &destRect, 0, 0, flip);
	}

	void VideoManager::drawFrame(const std::string& texture_id, int x, int y, int width, int height, int current_row, int current_frame, double angle, int alpha, SDL_RendererFlip flip) {
		SDL_Rect srcRect;
		SDL_Rect destRect;
		srcRect.x = width * current_frame;
		srcRect.y = height * current_row;
		srcRect.w = destRect.w = width;
		srcRect.h = destRect.h = height;
		destRect.x = x;
		destRect.y = y;

		SDL_SetTextureAlphaMod(texture_map[texture_id], alpha);
		SDL_RenderCopyEx(renderer, texture_map[texture_id], &srcRect, &destRect, angle, 0, flip);
	}

	void VideoManager::clear() {
		SDL_RenderClear(renderer);
	}

	void VideoManager::render()	{
		SDL_RenderPresent(renderer);
	}

	void VideoManager::destroy() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	SDL_Texture* VideoManager::load_texture(const std::string& filePath) {
		LOG("Loading texture: " + filePath);
		SDL_Texture* newTexture = IMG_LoadTexture(renderer, filePath.c_str());

		if (!newTexture) {
			LOG("Failed to load texture " + filePath + ":" + SDL_GetError());
			return NULL;
		}

		texture_map[filePath] = newTexture;
		return newTexture;
	}
	
	void VideoManager::clear_texture_map() {
		for (std::pair<std::string, SDL_Texture*> texture : texture_map) {
			SDL_DestroyTexture(texture.second);
		}

		texture_map.clear();
	}

	void VideoManager::clear_from_texture_map(const std::string id) {
		texture_map.erase(id);
	}
}

