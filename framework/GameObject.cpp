#include <algorithm>
#include "GameObject.h"
#include "VideoManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Box.h"
#include "Logger.h"

namespace Thing2D {
	GameObject::GameObject(const std::string& texture_id, float x, float y, int width, int height) :
		debug(false), visible(true), dead(false), flipped(false), life(1),
		alpha(255), angle(0), r(255), g(255), b(255),
		position(x, y), velocity(0, 0), acceleration(0, 0),
		width(width), height(height),
		curr_row(0), curr_col(0),
		texture_id(texture_id),
		video_manager(nullptr),
		input_manager(nullptr),
		audio_manager(nullptr),
		game(nullptr) {}

	GameObject::~GameObject() {
		destroy();
	}

	void GameObject::init() {
		create_box(position.x, position.y, width, height);
	}

	void GameObject::update() {
		if (dead) {
			return;
		}

		velocity += acceleration;
		position += velocity;

		std::for_each(boxes.begin(), boxes.end(), [&](auto box) {
			box->x = position.x;
			box->y = position.y;
		});
	}

	void GameObject::draw() {
		video_manager->draw(texture_id, (int)position.x, (int)position.y, width, height, visible,
							curr_row, curr_col, angle, alpha, r, g, b, flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE,
							debug, boxes);
	}

	void GameObject::destroy() {}

	void GameObject::create_box(float x, float y, int w, int h) {
		const std::string box_label = "box_" + std::to_string(boxes.size());
		create_box(x, y, w, h, box_label);
	}

	void GameObject::create_box(float x, float y, int w, int h, const std::string& box_label) {
		LOG("Create box");
		Box* box = new Box(x, y, w, h);
		box->label = box_label;
		box->active = true;
		boxes.push_back(box);
	}

	bool GameObject::overlaps(GameObject* target) {
		if (target->dead) {
			return false;
		}

		auto result = std::find_if(boxes.begin(), boxes.end(), [&](Box* this_box) {
			auto result = std::find_if(target->boxes.begin(), target->boxes.end(), [&](Box* target_box) {
				return this_box->check_sdl_intersection(target_box, debug);
			});
			
			return result != target->boxes.end();
		});

		return result != boxes.end();
	}

	void GameObject::move(const Vector& new_position) {
		position += new_position;
	}

	void GameObject::move(int x, int y) {
		position.x += x;
		position.y += y;
	}

	void GameObject::hurt(int damage) {
		life -= damage;

		if (life <= 0) {
			dead = true;
		}
	}
}