#include "State.h"
#include <algorithm>
#include "Game.h"
#include "Layer.h"

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

	void State::create_timer(const std::string& timer_id, float time_limit_ms) {
		timers[timer_id] = new Timer(time_limit_ms);
		timers[timer_id]->reset();
	}

	void State::create_layer() {
		Layer* new_layer = new Layer();
		new_layer->video_manager = video_manager;
		new_layer->input_manager = input_manager;
		new_layer->audio_manager = audio_manager;
		new_layer->game = game;
		layers.push_back(new_layer);
	}

	auto State::get_layer(int idx) {
		return layers[idx];
	}

	void State::add(const std::string& game_object_id, GameObject* game_object, int layer_idx) {
		Layer* layer = layers[layer_idx];
		layer->add(game_object_id, game_object);
	}

	void State::add(GameObject* game_object) {
		Layer* layer = layers[0];
		layer->add(game_object);
	}
	
	void State::update() {
		std::for_each(timers.begin(), timers.end(), [&](auto timer) {
			timer.second->update(game->delta_time());
		});

		std::for_each(layers.begin(), layers.end(), [](auto layer) {
			layer->update();
		});
	}

	void State::render() {
		std::for_each(layers.begin(), layers.end(), [](auto layer) {
			layer->render();
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