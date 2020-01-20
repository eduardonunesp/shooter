#include "GameObject.h"
#include "VideoManager.h"
#include "Logger.h"

namespace Thing2D {
	GameObject::GameObject(const std::string& filePath, int x, int y, int width, int height) :
		texture(NULL), position(x, y), velocity(0, 0), acceleartion(0, 0),
		width(width), height(height) {
		visible = true;
		dead = false;
		life = 1;
		rect.x = x;
		rect.y = y;
		load_texture(filePath);
	}

	void GameObject::update() {
		position += velocity;
	}

	void GameObject::draw() {
		if (!visible) {
			return;
		}

		SDL_Rect srcRect;
		SDL_Rect destRect;

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = destRect.w = width;
		srcRect.h = destRect.h = height;
		destRect.x = (int) position.x;
		destRect.y = (int) position.y;

		SDL_RenderCopy(VideoManager::get_instance()->get_renderer(), texture, &srcRect, &destRect);
	}

	void GameObject::destroy() {

	}

	bool GameObject::overlaps(GameObject* target) {
		if (!target) {
			return false;
		}

		return false;
	}

	void GameObject::load_texture(const std::string& filePath) {
		texture = VideoManager::get_instance()->load_texture(filePath);
	}
}