#include "VideoManager.h"
#include <algorithm>
#include <SDL_image.h>
#include "Logger.h"

namespace Thing2D {
	void VideoManager::init(int screen_width, int screen_height) {
		LOG("Initialize Video Manager");
		
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

	void VideoManager::draw(const std::string& texture_id, int x, int y, int width, int height, int current_row, int current_col, double angle, int alpha, SDL_RendererFlip flip) {
		SDL_Rect srcRect;
		SDL_Rect destRect;
		srcRect.x = width * current_col;
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
		LOG("Destroying VideoManager");
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	SDL_Texture* VideoManager::load_texture(const std::string& file_path, const std::string& texture_id) {
		LOG("Loading texture: " + file_path);
		SDL_Texture* newTexture = IMG_LoadTexture(renderer, file_path.c_str());

		if (!newTexture) {
			LOG("Failed to load texture " + file_path + ":" + SDL_GetError());
			return nullptr;
		}

		LOG("Texture: " + texture_id + ":" + file_path);
		texture_map[texture_id] = newTexture;
		return newTexture;
	}
	
	void VideoManager::clear_texture_map() {
		LOG("Clearing all texture map");
		std::for_each(texture_map.begin(), texture_map.end(), [](auto texture) {
			SDL_DestroyTexture(texture.second);
		});
		texture_map.clear();
	}

	void VideoManager::clear_from_texture_map(const std::string texture_id) {
		LOG("Remove texture: " + texture_id);
		texture_map.erase(texture_id);
	}
}

