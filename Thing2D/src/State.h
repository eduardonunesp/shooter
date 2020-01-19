#pragma once
#include <vector>

namespace Thing2D {
	class GameObject;
	class VideoManager;
	class InputManager;

	class State {
	public:
		virtual void Init();
		virtual void Update();

		void Add(GameObject* gameObject);
		void Draw();
		void Destroy();

	private:
		std::vector<GameObject*> gameObjects;
	};
}