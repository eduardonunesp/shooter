#include <algorithm>
#include <SDL_image.h>
#include "VideoManager.h"
#include "Collider.h"
#include "Logger.h"

#define PREFERED_DRIVER "opengl"

namespace Thing2D {
	void VideoManager::init(int screen_width, int screen_height) {
		LOG("Initialize Video Manager");
		
		if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
			throw "Couldn't initialize SDL";
		}

		int prefered_render_driver = -1;

		int r_drivers = SDL_GetNumRenderDrivers();
		LOG("RENDER DRIVERS: " << r_drivers);
		
		for (int i = 0; i < r_drivers; i++) {
			SDL_RendererInfo renderer_info;
			SDL_GetRenderDriverInfo(i, &renderer_info);
			LOG("Renderer driver available: " << renderer_info.name);

			if (renderer_info.name == std::string(PREFERED_DRIVER)) {
				prefered_render_driver = i;
			}
		}

		LOG("Using render driver: " << prefered_render_driver);

		int v_drivers = SDL_GetNumVideoDrivers();
		LOG("VIDEO DRIVERS: " << v_drivers);

		for (int i = 0; i < v_drivers; i++) {
			LOG("Video driver available: " << SDL_GetVideoDriver(i));
		}

		int window_flags = SDL_WINDOW_OPENGL ;
	
#ifdef ALLOW_HIGHDPI
		window_flags |= SDL_WINDOW_ALLOW_HIGHDPI
#endif

		window = SDL_CreateWindow("GAME WINDOW", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, window_flags);

		if (!window) {
			throw "Couldn't create window";
		}

		int renderer_flags = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED;

		renderer = SDL_CreateRenderer(window, prefered_render_driver, renderer_flags);

		if (!renderer) {
			throw "Couldn't create renderer";
		}

		int w, h;
		SDL_GetWindowSize(window, &w, &h);

		int display_count = SDL_GetNumVideoDisplays() - 1;
		LOG("Display count: " << display_count);

		int display_mode_count = SDL_GetNumDisplayModes(0);
		LOG("Display mode count: " << display_mode_count);

		SDL_DisplayMode mode;
		Uint32 f;

		for (int i = 0; i < display_mode_count; ++i) {
			if (SDL_GetDisplayMode(0, i, &mode) != 0) {
				ERR("SDL_GetDisplayMode failed: " << SDL_GetError());
				break;
			}

			f = mode.format;

			SDL_Log("Mode %i\tbpp %i\t%s\t%i x %i Hz %i", i,
				SDL_BITSPERPIXEL(f), SDL_GetPixelFormatName(f), mode.w, mode.h, mode.refresh_rate);
		}

		SDL_DisplayMode curr_mode;
		SDL_GetCurrentDisplayMode(display_count, &curr_mode);
		SDL_Log("Current Display Mode %i\tbpp %i\t%s\t%i x %i Hz %i", display_count,
			SDL_BITSPERPIXEL(f), SDL_GetPixelFormatName(f), curr_mode.w, curr_mode.h, curr_mode.refresh_rate);
		refresh_rate = curr_mode.refresh_rate;

		SDL_DisplayMode curr_desktop_mode;
		SDL_GetDesktopDisplayMode(display_count, &curr_desktop_mode);
		SDL_Log("Current Desktop Mode %i\tbpp %i\t%s\t%i x %i Hz %i", display_count,
			SDL_BITSPERPIXEL(f), SDL_GetPixelFormatName(f), curr_desktop_mode.w, curr_desktop_mode.h, curr_desktop_mode.refresh_rate);

		color_cycle.push_back(Color::red());
		color_cycle.push_back(Color::green());
		color_cycle.push_back(Color::blue());

		LOG("VideoManager Ready " + std::to_string(w) + ":" + std::to_string(h));
	}

	void VideoManager::render(const std::string& texture_id, int dest_x, int dest_y, int dest_width, int dest_height, bool visible,
		int current_row, int current_col, double angle, int alpha, int r, int g, int b, SDL_RendererFlip flip,
		bool debug, std::vector<Collider*> debug_boxes) {
		SDL_Rect srcRect;
		SDL_Rect destRect;
		srcRect.x = dest_width * current_col;
		srcRect.y = dest_height * current_row;
		srcRect.w = destRect.w = dest_width;
		srcRect.h = destRect.h = dest_height;
		destRect.x = dest_x;
		destRect.y = dest_y;

		auto texture = texture_map[texture_id];
		if (texture) {
			SDL_SetTextureColorMod(texture, r, g, b);

			if (visible) {
				SDL_SetTextureAlphaMod(texture, alpha);
				SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);
			}

			if (debug) {
				unsigned int count = 0;
				std::for_each(debug_boxes.begin(), debug_boxes.end(), [&](auto box) {
					if (count > color_cycle.size()) {
						count = 0;
					}

					Color c = color_cycle[count];
					box->debug(renderer, c);
					count++;
				});
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}
		}
	}

	void VideoManager::clear() {
		SDL_RenderClear(renderer);
	}

	void VideoManager::present()	{
		SDL_RenderPresent(renderer);
	}

	void VideoManager::destroy() {
		LOG("Destroying VideoManager");
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void VideoManager::load_texture(const std::string& file_path, const std::string& texture_id) {
		LOG("Loading texture: " + file_path);
		auto newTexture = IMG_LoadTexture(renderer, file_path.c_str());

		if (!newTexture) {
			LOG("Failed to load texture " + file_path + ": " + IMG_GetError());
			throw "Failed to load texture";
		}

		LOG("Texture: " + texture_id + ":" + file_path);
		texture_map[texture_id] = newTexture;
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

