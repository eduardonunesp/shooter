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
		void add(const std::string& game_object_id, GameObject* game_object) override;
		void add(GameObject* game_object) override;
		void add(Group* other_group) override;

	protected:
		friend class State;

		VideoManager* video_manager;
		InputManager* input_manager;
		AudioManager* audio_manager;
		Game* game;

		unsigned int order;
	};
}
