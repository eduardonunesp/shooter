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

		// Life cycle
		virtual void init();
		virtual void update();
		virtual void render();
		virtual void destroy();

		// Colliders
		void create_collider(float x, float y, int w, int h);
		void create_collider(float x, float y, int w, int h, const std::string& label);
		inline auto get_collider(int collider_idx) { return colliders[collider_idx]; }
		bool overlaps(GameObject* target);

		// Basic physics
		void set_velocity(const Vector& velocity_value);
		void add_velocity(const Vector& new_velocity);
		void move(const Vector& new_position);
		void move(int x, int y);
		void set_texture_row_col(int row, int col);
		void set_texture_margin_space(int margin, int spacing);
		void set_position(float x, float y);
		void set_position(const Vector& new_position);

		// Identification
		inline void set_tag(const std::string& tag_value) { tag = tag_value; }
		inline void set_label(const std::string& label_value) { label = label_value; }
		inline const std::string& get_label() { return label; }
		inline const Vector& get_position() { return position; }

		// Geometry
		inline int get_width() { return width; }
		inline int get_height() { return height; }

		// Basic game object logic
		void reset();
		void kill();
		void hurt(int damage);

		// Queries
		inline bool is_visible() { return visible; }
		inline bool is_dead() { return dead; }
		inline bool is_flipped() { return flipped; }

	protected:
		friend class Group;
		friend class Layer;

		std::string label;
		std::string tag;

		bool debug;

		bool dead; // == disabled
		int life;

		bool visible;
		bool flipped;
		int r, g, b;
		int alpha;
		double angle;

		Vector position;
		Vector velocity;
		Vector acceleration;
		std::vector<Collider*> colliders;

		int width, height;
		int curr_texture_row, curr_texture_col;
		int curr_texture_margin, curr_texture_spacing;
		std::string texture_id;

		VideoManager* video_manager;
		InputManager* input_manager;
		AudioManager* audio_manager;
		Game* game;
	};
}
