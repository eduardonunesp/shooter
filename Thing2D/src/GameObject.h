#pragma once

#include <SDL.h>
#include <string>

namespace Thing2D {
	class GameObject {
	public:
		explicit GameObject(const std::string& filePath, int x, int y, int width, int height);

		void update();
		void draw();
		void destroy();
		bool overlaps(GameObject* target);
		void load_texture(const std::string& filePath);
		
		inline void set_visible(bool value) { visible = value; }
		inline void set_life(int value) { life = value; }
		inline void set_dead(bool value) { dead = value; }

		inline bool is_visible() { return visible; }
		inline bool is_dead() { return dead; }
		
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
		bool visible;
		bool dead;
		int life;
		int x, y;
		int width, height;
		SDL_Rect rect;
		SDL_Texture* texture;
	};
}