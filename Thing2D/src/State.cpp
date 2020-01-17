#include "State.h"
#include "GameObject.h"
#include "Logger.h"

namespace Thing2D {
	void State::Init() {
		LOG("Initialize scene");
	}

	void State::Update() {
		for (GameObject* gameObject : gameObjects) {
			gameObject->Update();
		}
	}

	void State::Add(GameObject* gameObject)	{
		LOG("Adding game object");

		if (gameObject) {
			gameObjects.push_back(gameObject);
		}
	}

	void State::Draw() {
		for (GameObject* gameObject : gameObjects) {
			gameObject->Draw();
		}
	}

	void State::Destroy() {
		for (GameObject* gameObject : gameObjects) {
			gameObject->Destroy();
		}
	}
}