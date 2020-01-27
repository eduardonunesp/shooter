#pragma once

#include "Group.h"

namespace Thing2D {
	class VideoManager;
	class InputManager;
	class AudioManager;
	class Game;

	class Layer : public Group {
	public:
		Layer();
		Layer(int order);
		Layer(float x, float y);

		virtual void render();

		// Adding game objects
		void add(const std::string& game_object_id, GameObject* game_object) override;
		void add(GameObject* game_object) override;

		// Setters
		inline void set_order(int order_value) {
			order = order_value;
		}

	protected:
		friend class State;

		VideoManager* video_manager;
		InputManager* input_manager;
		AudioManager* audio_manager;
		Game* game;

		int order;
	};
}
