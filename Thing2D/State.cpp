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
	}

	void State::create_timer(const std::string& timer_id, float time_limit_ms) {
		timers[timer_id] = new Timer(time_limit_ms);
		timers[timer_id]->reset();
	}

	void State::add_layer(Layer* layer) {
		layer->video_manager = video_manager;
		layer->input_manager = input_manager;
		layer->audio_manager = audio_manager;
		layer->game = game;

		if (layers.size() > 0) {
			layer->order = static_cast<int>(layers.size());
		}

		layer->init();
		layers.push_back(layer);

		sort_layers_by_order();

		LOG("Layer " << layer->label << " added in order " << layer->order);
	}

	void State::create_layer(unsigned int order) {
		Layer* new_layer = new Layer(order);

		if (layers.size() == 0) {
			new_layer->label = "default layer";
			default_layer = new_layer;
		}

		if (order == 0 && layers.size() > 0) {
			new_layer->order = static_cast<int>(layers.size());
		}

		new_layer->order = static_cast<int>(layers.size());
		new_layer->video_manager = video_manager;
		new_layer->input_manager = input_manager;
		new_layer->audio_manager = audio_manager;
		new_layer->game = game;

		new_layer->init();
		layers.push_back(new_layer);

		sort_layers_by_order();

		LOG("Layer " << new_layer->label << " added in order " << new_layer->order);
	}

	Layer* State::get_layer(int idx) {
		return layers[idx];
	}

	void State::add(const std::string& game_object_id, GameObject* game_object) {
		default_layer->add(game_object_id, game_object);
	}

	void State::add(const std::string& game_object_id, GameObject* game_object, int layer_idx) {
		Layer* layer = layers[layer_idx];
		layer->add(game_object_id, game_object);
	}

	void State::add(GameObject* game_object) {
		default_layer->add(game_object);
	}

	void State::sort_layers_by_order() {
		std::sort(layers.begin(), layers.end(), [](auto layer_a, auto layer_b) {
			return layer_a->order > layer_b->order;
		});
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