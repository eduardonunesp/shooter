#pragma once

#include <map>
#include <string>
#include <vector>
#include "Timer.h"

namespace Thing2D {
	class GameObject;
	class Layer;
	class VideoManager;
	class InputManager;
	class AudioManager;
	class Game;

	class State {
	public:
		State();

		// Life cycle
		virtual void init();
		virtual void update();
		virtual void render();
		virtual void destroy();

		// Timer
		void create_timer(const std::string& timer_id, float time_limit_ms);
		auto get_timer(const std::string& timer_id) {
			return timers[timer_id];
		}

		// Layers
		void add_layer(Layer* layer);
		void create_layer(unsigned int order = 0);
		Layer* get_layer(int idx);

		// Add game object suggar function
		void add(const std::string& game_object_id, GameObject* game_object);
		void add(const std::string& game_object_id, GameObject* game_object, int layer_idx);
		void add(GameObject* game_object);

	protected:
		friend class Game;

		VideoManager* video_manager;
		InputManager* input_manager;
		AudioManager* audio_manager;
		Game* game;

		void sort_layers_by_order();

		Layer* default_layer;
		std::vector<Layer*> layers;
		std::map<std::string, Timer*> timers;
	};
}
