#include "State.h"
#include <algorithm>
#include "Game.h"
#include "Group.h"

namespace Thing2D {
	State::State() : 
		video_manager(nullptr),
		input_manager(nullptr),
		audio_manager(nullptr),
		game(nullptr),
		default_layer(nullptr) {}

	void State::init() {
		create_layer();
		default_layer = layers[0];
	}

	void State::create_timer(const std::string& timer_id, int time_limit_ms) {
		timers[timer_id] = new Timer(time_limit_ms);
		timers[timer_id]->reset();
	}

	void State::create_layer() {
		Group* layerGroup = new Group();
		layerGroup->video_manager = video_manager;
		layerGroup->input_manager = input_manager;
		layerGroup->audio_manager = audio_manager;
		layerGroup->game = game;
		layers.push_back(layerGroup);
	}

	void State::add(const std::string& game_object_id, GameObject* game_object, int layer_idx) {
		Group* layerGroup = layers[layer_idx];
		layerGroup->add(game_object_id, game_object);
	}

	void State::add(GameObject* game_object) {
		Group* layerGroup = layers[0];
		layerGroup->add(game_object);
	}
	
	void State::update() {
		std::for_each(timers.begin(), timers.end(), [&](auto timer) {
			timer.second->update(game->delta_time());
		});

		std::for_each(layers.begin(), layers.end(), [](auto layer) {
			layer->update();
		});
	}

	void State::draw() {
		std::for_each(layers.begin(), layers.end(), [](auto layer) {
			layer->draw();
		});
	}

	void State::destroy() {
		std::for_each(timers.begin(), timers.end(), [](auto timer) {
			delete timer.second;
		});

		std::for_each(layers.begin(), layers.end(), [](auto layer) {
			layer->destroy();
		});
	}
}