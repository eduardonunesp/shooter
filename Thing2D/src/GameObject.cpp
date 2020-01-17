#include "GameObject.h"
#include "VideoManager.h"
#include "Logger.h"

namespace Thing2D {
	GameObject::GameObject(VideoManager* videoManager) : videoManager(videoManager), x(0), y(0), texture(NULL) {
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

		int w, h;
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = destRect.w = w;
		srcRect.h = destRect.h = h;
		destRect.x = x;
		destRect.y = y;

		SDL_RenderCopy(videoManager->GetRenderer(), texture, &srcRect, &destRect);
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
		texture = videoManager->LoadTexture(filePath);
	}
}