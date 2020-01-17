#pragma once
#include <vector>

namespace Thing2D {
	class GameObject;
	class VideoManager;

	class State {
	public:
		void SetVideoManager(VideoManager* videoManager) {
			this->videoManager = videoManager;
		}
		virtual void Init();
		void Update();
		void Add(GameObject* gameObject);
		void Draw();
		void Destroy();

	protected:
		VideoManager* videoManager;

	private:
		std::vector<GameObject*> gameObjects;
	};
}