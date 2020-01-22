#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include <map>
#include "Color.h"

namespace Thing2D {
	class Box;

	class VideoManager {
	public:
		VideoManager() : refresh_rate(60), window(nullptr), renderer(nullptr) {}
		~VideoManager() { destroy(); }

		// Life cycle functions
		void init(int screen_width, int screen_height);
		void draw(const std::string& texture_id, int x, int y, int width, int height, bool visible,
			int current_row, int current_frame, double angle, int alpha, int r, int g, int b, SDL_RendererFlip flip,
			bool debug, std::vector<Box*> debug_boxes);
		void clear();
		void render();
		void destroy();

		// Video stuff
		inline int get_refresh_rate() { return refresh_rate;  }
		inline auto get_renderer() { return renderer; }

		// Texture functions
		void load_texture(const std::string& file_path, const::std::string& texture_id);
		void clear_texture_map();
		void clear_from_texture_map(const std::string texture_id);

	private:
		std::vector<Color> color_cycle;
		int refresh_rate;
		SDL_Window* window;
		SDL_Renderer* renderer;
		std::map<std::string, SDL_Texture*> texture_map;
		static VideoManager* instance;
	};
}
