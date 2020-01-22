#pragma once

#include <SDL_rect.h>

namespace Thing2D {
	class Rect {
	public:
		Rect(float x, float y, int h, int w) :
			x(x), y(y), h(h), w(w), offset_x(0), offset_y(0) {}

		float offset_x, offset_y;
		float x, y;
		int h, w;

		inline SDL_Rect to_sdl_rect() {
			SDL_Rect rect;
			rect.x = (int)x - offset_x;
			rect.y = (int)y - offset_y;
			rect.h = h;
			rect.w = w;
			return rect;
		}

		const static int buffer = 4;

		bool overlaps(Rect* other_rect) {
			int aHBuf = this->h / buffer;
			int aWBuf = this->w / buffer;

			int bHBuf = other_rect->h / buffer;
			int bWBuf = other_rect->w / buffer;

			if ((this->y + this->h) - aHBuf <= other_rect->y + bHBuf) { return false; }
			if (this->y + aHBuf >= (other_rect->y + other_rect->h) - bHBuf) { return false; }
			if ((this->x + this->w) - aWBuf <= other_rect->x + bWBuf) { return false; }
			if (this->x + aWBuf >= (other_rect->x + other_rect->w) - bWBuf) { return false; }

			return true;
		}
	};
}
