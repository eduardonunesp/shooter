#pragma once

#include <SDL.h>
#include <string>
#include "Vector.h"
#include "Rect.h"

namespace Thing2D {
	class Vector;

	class GameObject {
	public:
		explicit GameObject(const std::string& texture_id, float x, float y, int width, int height);

		void update();
		void draw();
		void destroy();
		bool overlaps(GameObject* target);
		
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

		Vector position;
		Vector velocity;
		Vector acceleartion;
		Rect rect;

	protected:
		int width, height;
		std::string texture_id;
	};
}