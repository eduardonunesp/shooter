#pragma once
#include <vector>

namespace Thing2D {
	class GameObject;
	class VideoManager;
	class InputManager;

	class State {
	public:
		void SetVideoManager(VideoManager* videoManager) {
			this->videoManager = videoManager;
		}

		void SetInputManager(InputManager* inputManager) {
			this->inputManager = inputManager;
		}

		virtual void Init();
		virtual void Update();

		void Add(GameObject* gameObject);
		void Draw();
		void Destroy();

	protected:
		VideoManager* videoManager;
		InputManager* inputManager;

	private:
		std::vector<GameObject*> gameObjects;
	};
}