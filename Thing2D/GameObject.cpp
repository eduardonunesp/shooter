#include <algorithm>
#include "GameObject.h"
#include "VideoManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Collider.h"
#include "Logger.h"

namespace Thing2D {
	GameObject::GameObject(const std::string& texture_id, float x, float y, int width, int height) :
		debug(false), visible(true), dead(false), flipped(false), life(1),
		r(255), g(255), b(255), alpha(255), angle(0), 
		position(x, y), velocity(0, 0), acceleration(0, 0),
		width(width), height(height),
		curr_texture_row(0), curr_texture_col(0),
		texture_id(texture_id),
		video_manager(nullptr),
		input_manager(nullptr),
		audio_manager(nullptr),
		game(nullptr) {}

	GameObject::~GameObject() {
		destroy();
	}

	void GameObject::init() {
		create_collider(position.x, position.y, width, height);
	}

	void GameObject::update() {
		if (dead) {
			return;
		}

		velocity += acceleration;
		position += velocity;

		std::for_each(colliders.begin(), colliders.end(), [&](auto box) {
			box->x = box->offset_x + position.x;
			box->y = box->offset_y + position.y;
		});
	}

	void GameObject::render() {
		if (!dead) {
			// TODO: Don't render objects out of the game screen
			video_manager->render(texture_id, (int)position.x, (int)position.y, curr_texture_margin, curr_texture_spacing, width, height, visible,
				curr_texture_row, curr_texture_col, angle, alpha, r, g, b, flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE,
				debug, colliders);
		}
	}

	void GameObject::destroy() {}

	void GameObject::create_collider(float x, float y, int w, int h) {
		const std::string box_label = "box_" + std::to_string(colliders.size()) + " for " + label;
		create_collider(x, y, w, h, box_label);
	}

	void GameObject::create_collider(float x, float y, int w, int h, const std::string& box_label) {
		if (dead) {
			return;
		}

		LOG("Create box for " << label);
		Collider* box = new Collider(x, y, w, h);
		box->label = box_label;
		box->active = true;
		colliders.push_back(box);
	}

	bool GameObject::overlaps(GameObject* target) {
		if (target->dead) {
			return false;
		}

		auto result = std::find_if(colliders.begin(), colliders.end(), [&](Collider* this_box) {
			auto result = std::find_if(target->colliders.begin(), target->colliders.end(), [&](Collider* target_box) {
				return this_box->check_sdl_intersection(target_box, debug);
			});
			
			return result != target->colliders.end();
		});

		return result != colliders.end();
	}

	void GameObject::set_velocity(const Vector& velocity_value) {
		velocity = velocity_value;
	}

	void GameObject::move(const Vector& new_position) {
		if (dead) {
			return;
		}

		position += new_position;
	}

	void GameObject::move(int x, int y) {
		if (dead) {
			return;
		}

		position.x += x;
		position.y += y;
	}

	void GameObject::set_texture_row_col(int row, int col) {
		curr_texture_row = row;
		curr_texture_col = col;
	}

	void GameObject::set_texture_margin_space(int margin, int spacing) {
		curr_texture_margin = margin;
		curr_texture_spacing = spacing;
	}

	void GameObject::set_position(int x, int y) {
		position.x = x;
		position.y = y;
	}

	void GameObject::set_position(const Vector& new_position) {
		position = new_position;
	}

	void GameObject::add_velocity(const Vector& new_velocity) {
		velocity += new_velocity;
	}

	void GameObject::reset() {
		if (dead) {
			dead = false;
			life = 1;
			position = Vector::zero();
		}
	}

	void GameObject::kill() {
		LOG("Kill " + label);
		dead = true;
		life = 0;
	}

	void GameObject::hurt(int damage) {
		if (dead) {
			return;
		}

		LOG("Hurt " << label << " with damage of " << damage);

		life -= damage;

		if (life <= 0) {
			kill();
		}
	}
}