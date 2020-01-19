#pragma once
#include <vector>

namespace Thing2D {
	class GameObject;
	class VideoManager;
	class InputManager;

	class State {
	public:
		virtual void init();
		virtual void update();

		void add(GameObject* game_object);
		void draw();
		void destroy();

	private:
		std::vector<GameObject*> game_objects;
	};
}