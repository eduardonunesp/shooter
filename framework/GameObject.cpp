#include "GameObject.h"
#include "VideoManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Logger.h"

namespace Thing2D {
	GameObject::GameObject(const std::string& texture_id, float x, float y, int width, int height) :
		visible(true), dead(false), flipped(false), life(1),
		alpha(255), angle(0),
		position(x, y), velocity(0, 0), acceleration(0, 0), rect(x, y, width, height),
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

	void GameObject::update() {
		if (dead) {
			return;
		}

		velocity += acceleration;
		position += velocity;

		rect.x = position.x;
		rect.y = position.y;
	}

	void GameObject::draw() {
		if (!visible) {
			return;
		}

		video_manager->draw(texture_id, (int)position.x, (int)position.y, width, height, curr_row, curr_col, angle, alpha, flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	}

	void GameObject::destroy() {}

	bool GameObject::overlaps(GameObject* target) {
		if (target->rect.overlaps(&this->rect)) {
			return true;
		}

		return false;
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