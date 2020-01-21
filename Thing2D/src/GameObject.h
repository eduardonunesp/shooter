#pragma once

#include <SDL.h>
#include <string>
#include "Vector.h"
#include "Rect.h"

namespace Thing2D {
	class Vector;
	class VideoManager;
	class InputManager;

	class GameObject {
	public:
		GameObject(const std::string& texture_id, float x, float y, int width, int height);
		virtual ~GameObject();

		virtual void update();
		virtual void draw();
		virtual void destroy();

		bool overlaps(GameObject* target);

		void move(const Vector& new_position);
		void move(int x, int y);
		void hurt(int damage);

		inline bool is_visible() { return visible; }
		inline bool is_dead() { return dead; }
		inline bool is_flipped() { return flipped; }

	protected:
		friend class Group;

		bool visible;
		bool dead;
		bool flipped;
		int life;

		int alpha;
		double angle;

		Vector position;
		Vector velocity;
		Vector acceleartion;
		Rect rect;

		int width, height;
		int curr_row, curr_col;
		std::string texture_id;

		VideoManager* video_manager;
		InputManager* input_manager;
	};
}
