#pragma once

#include <string>
#include "Rect.h"
#include "Color.h"
#include "Logger.h"

namespace Thing2D {
	class Collider : public Rect {
	public:
		Collider(float x, float y, int h, int w): 
			Rect(x, y, h, w),
			active(true),
			offset_x(0), offset_y(0) {}

		std::string label;
		bool active;
		float offset_x, offset_y;

		inline SDL_Rect to_sdl_rect() {
			SDL_Rect box;
			box.x = (int)(x + offset_x);
			box.y = (int)(y + offset_y);
			box.h = h;
			box.w = w;
			return box;
		}

		virtual inline bool check_sdl_intersection(Collider* other_rect, bool debug) {
			if (!active) {
				return false;
			}

			SDL_Rect this_sdl_rect = to_sdl_rect();
			SDL_Rect other_sdl_rect = other_rect->to_sdl_rect();
			bool has_intersection = SDL_HasIntersection(&this_sdl_rect, &other_sdl_rect);

			if (has_intersection && debug) {
				LOG("Collision on box: " << label);
			}

			return has_intersection;
		}

		void debug(SDL_Renderer *renderer, const Color& color) {
			if (!active) {
				return;
			}

			SDL_Rect d_rect = to_sdl_rect();
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_RenderDrawRect(renderer, &d_rect);
		}
	};
}