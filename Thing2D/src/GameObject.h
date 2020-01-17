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
			x = newX;
			y = newY;
		}

	private:
		VideoManager* videoManager;
		int x, y;
		SDL_Rect rect;
		SDL_Texture* texture;
	};
}