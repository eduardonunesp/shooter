#pragma once

#include <SDL.h>
#include <string>
#include <map>

namespace Thing2D {
	class VideoManager {
	public:
		static VideoManager* get_instance() {
			if (!instance) {
				instance = new VideoManager();
			}

			return instance;
		}

		void init(int screen_width, int screen_height);
		void clear();
		void render();
		void destroy();
		inline SDL_Renderer* get_renderer() { return renderer; }
		SDL_Texture* load_texture(const std::string& filePath);
		void clear_texture_map();
		void clear_from_texture_map(const std::string textureId);

	private:
		VideoManager() : window(NULL), renderer(NULL) {}
		~VideoManager() { destroy(); }

		SDL_Window* window;
		SDL_Renderer* renderer;
		std::map<std::string, SDL_Texture*> texture_map;
		static VideoManager* instance;
	};
}
