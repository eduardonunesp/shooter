#pragma once

#include <SDL.h>
#include <string>

namespace Thing2D {
	class GameObject {
	public:
		explicit GameObject(int x, int y, int width, int height);

		void update();
		void draw();
		void destroy();
		bool overlaps(GameObject* target);
		void load_texture(const std::string& filePath);
		
		inline void move(int newX, int newY) {
			x += newX;
			y += newY;
		}

		inline void hurt(int damage) {
			life -= damage;

			if (life <= 0) {
				dead = true;
			}
		}

	protected:
		bool dead;
		int life;
		int x, y;
		int width, height;
		SDL_Rect rect;
		SDL_Texture* texture;
	};
}