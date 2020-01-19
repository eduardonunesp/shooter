#include "State.h"
#include "GameObject.h"
#include "Logger.h"

namespace Thing2D {
	void State::init() {
		LOG("Initialize scene");
	}

	void State::update() {
		for (GameObject* gameObject : game_objects) {
			gameObject->update();
		}
	}

	void State::add(GameObject* gameObject)	{
		LOG("Adding game object");

		if (gameObject) {
			game_objects.push_back(gameObject);
		}
	}

	void State::draw() {
		for (GameObject* gameObject : game_objects) {
			gameObject->draw();
		}
	}

	void State::destroy() {
		for (GameObject* gameObject : game_objects) {
			gameObject->destroy();
		}
	}
}