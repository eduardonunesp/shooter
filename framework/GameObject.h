#pragma once

#include <SDL.h>
#include <string>
#include <vector>
#include "Vector.h"

namespace Thing2D {
	class Collider;
	class VideoManager;
	class InputManager;
	class AudioManager;
	class Game;

	class GameObject {
	public:
		GameObject(const std::string& texture_id, float x, float y, int width, int height);
		virtual ~GameObject();

		virtual void init();
		virtual void update();
		virtual void draw();
		virtual void destroy();

		void create_box(float x, float y, int w, int h);
		void create_box(float x, float y, int w, int h, const std::string& label);
		inline auto get_box(int box_idx) { return boxes[box_idx]; }
		bool overlaps(GameObject* target);

		void set_velocity(const Vector& velocity_value);
		inline void set_tag(const std::string& tag_value) { tag = tag_value; }
		inline void set_label(const std::string& label_value) { label = label_value; }

		void move(const Vector& new_position);
		void move(int x, int y);
		void kill();
		void hurt(int damage);

		inline const std::string& get_label() { return label; }
		inline const Vector& get_position() { return position; }

		inline bool is_visible() { return visible; }
		inline bool is_dead() { return dead; }
		inline bool is_flipped() { return flipped; }

	protected:
		friend class Group;

		std::string label;
		std::string tag;

		bool debug;
		bool visible;
		bool dead; // == disabled
		bool flipped;
		int life;

		int r, g, b;
		int alpha;
		double angle;

		Vector position;
		Vector velocity;
		Vector acceleration;
		std::vector<Collider*> boxes;

		int width, height;
		int curr_row, curr_col;
		std::string texture_id;

		VideoManager* video_manager;
		InputManager* input_manager;
		AudioManager* audio_manager;
		Game* game;
	};
}
