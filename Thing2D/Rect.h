#pragma once

#include <SDL_rect.h>

namespace Thing2D {
	class Rect {
	public:
		Rect(float x, float y, int h, int w) :
			x(x), y(y), h(h), w(w) {}

		float x, y;
		int h, w;

		virtual inline SDL_Rect to_sdl_rect() {
			SDL_Rect box;
			box.x = (int)x;
			box.y = (int)y;
			box.h = h;
			box.w = w;
			return box;
		}
	};
}
