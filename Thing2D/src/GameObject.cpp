#include "GameObject.h"
#include "VideoManager.h"
#include "Logger.h"

namespace Thing2D {
	GameObject::GameObject(const std::string& texture_id, float x, float y, int width, int height) :
		texture_id(texture_id), position(x, y), velocity(0, 0), acceleartion(0, 0),
		width(width), height(height), rect(x, y, width, height) {
		visible = true;
		dead = false;
		life = 1;
	}

	void GameObject::update() {
		velocity += acceleartion;
		position += velocity;
		rect.x = position.x;
		rect.y = position.y;
	}

	void GameObject::draw() {
		if (!visible) {
			return;
		}

		VideoManager::get_instance()->draw(texture_id, (int)position.x, (int)position.y, width, height, SDL_FLIP_NONE);
	}

	void GameObject::destroy() {

	}

	bool GameObject::overlaps(GameObject* target) {
		if (!target) {
			return false;
		}

		return false;
	}
}