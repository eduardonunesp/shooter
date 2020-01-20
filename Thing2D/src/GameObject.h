#pragma once

#include <SDL.h>
#include <string>
#include "Vector.h"

namespace Thing2D {
	class Vector;

	class GameObject {
	public:
		explicit GameObject(const std::string& filePath, float x, float y, int width, int height);

		void update();
		void draw();
		void destroy();
		bool overlaps(GameObject* target);
		void load_texture(const std::string& filePath);
		
		inline void move(const Vector &new_position) {
			position += new_position;
		}

		inline void move(int x, int y) {
			position.x += x;
			position.y += y;
		}
		
		inline void hurt(int damage) {
			life -= damage;

			if (life <= 0) {
				dead = true;
			}
		}

		bool visible;
		bool dead;
		int life;
		int width, height;

		Vector position;
		Vector velocity;
		Vector acceleartion;
	
	protected:
		SDL_Rect rect;
		SDL_Texture* texture;
	};
}