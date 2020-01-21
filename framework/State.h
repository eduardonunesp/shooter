#pragma once

#include "Group.h"

namespace Thing2D {
	class GameObject;

	class State : public Group {
	public:
		State() : Group() {}

	protected:
		friend class Game;
	};
}
