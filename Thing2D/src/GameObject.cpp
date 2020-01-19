#include "GameObject.h"
#include "VideoManager.h"
#include "Logger.h"

namespace Thing2D {
	GameObject::GameObject(int x, int y, int width, int height) : texture(NULL) {
		this->x = x;
		this->y = y;
		dead = false;
		life = 1;
		this->width = width;
		this->height = height;
		rect.x = x;
		rect.y = y;
	}

	void GameObject::Update() {
		rect.x = x;
		rect.y = y;
	}

	void GameObject::Draw() {
		SDL_Rect srcRect;
		SDL_Rect destRect;

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = destRect.w = width;
		srcRect.h = destRect.h = height;
		destRect.x = x;
		destRect.y = y;

		SDL_RenderCopy(VideoManager::Instance()->GetRenderer(), texture, &srcRect, &destRect);
	}

	void GameObject::Destroy() {

	}

	bool GameObject::Overlaps(GameObject* target) {
		if (!target) {
			return false;
		}

		return false;
	}

	void GameObject::LoadTexture(const std::string& filePath) {
		texture = VideoManager::Instance()->LoadTexture(filePath);
	}
}