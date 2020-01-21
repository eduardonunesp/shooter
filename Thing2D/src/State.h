#pragma once

#include "Group.h"

namespace Thing2D {
	class VideoManager;
	class InputManager;

	class State : public Group {
	public:
		State() : 
			Group(), 
			video_manager(NULL), 
			input_manager(NULL) {}

	protected:
		friend class Game;
		VideoManager* video_manager;
		InputManager* input_manager;
	};
}