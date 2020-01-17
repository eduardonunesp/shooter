#pragma once

#include <SDL.h>
#include <string>

namespace Thing2D {
	class VideoManager;

	class GameObject {
	public:
		explicit GameObject(VideoManager* videoManager);

		void Update();
		void Draw();
		void Destroy();
		bool Overlaps(GameObject* target);
		void LoadTexture(const std::string& filePath);
		inline void Move(int newX, int newY) {
			x += newX;
			y += newY;
		}

		int x, y;

	private:
		VideoManager* videoManager;
		SDL_Rect rect;
		SDL_Texture* texture;
	};
}