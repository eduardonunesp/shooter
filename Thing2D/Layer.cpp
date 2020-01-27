#include <algorithm>
#include "Layer.h"
#include "Logger.h"
#include "GameObject.h"
#include "VideoManager.h"
#include "InputManager.h"
#include "AudioManager.h"


namespace Thing2D {
	Layer::Layer() : 
		Layer(0) {}

	Layer::Layer(int order) :
		Group(), 
		order(order),
		video_manager(nullptr),
		input_manager(nullptr),
		audio_manager(nullptr),
		game(nullptr) {}

	Layer::Layer(float x, float y) : 
		Group(x, y),
		order(0),
		video_manager(nullptr),
		input_manager(nullptr),
		audio_manager(nullptr),
		game(nullptr) {}

	void Layer::add(const std::string& game_object_id, GameObject* game_object) {
		if (game_object) {
			game_object->video_manager = video_manager;
			game_object->input_manager = input_manager;
			game_object->audio_manager = audio_manager;
			game_object->game = game;
			game_object->init();
			Group::add(game_object_id, game_object);
		} else {
			ERR("Game object is NULL");
		}
	}

	void Layer::add(GameObject* game_object) {
		if (game_object) {
			game_object->video_manager = video_manager;
			game_object->input_manager = input_manager;
			game_object->audio_manager = audio_manager;
			game_object->game = game;
			game_object->init();
			Group::add(game_object);
		} else {
			ERR("Game object is NULL");
		}
	}

	void Layer::render() {
		if (!visible) {
			return;
		}

		std::for_each(game_objects.begin(), game_objects.end(), [](auto game_object) {
			if (!game_object->dead) {
				return game_object->render();
			}
		});
	}
}
