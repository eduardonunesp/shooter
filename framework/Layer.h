#pragma once

#include "Group.h"

namespace Thing2D {
	class Layer : public Group {
	public:
		Layer();
		Layer(int order);
		Layer(float x, float y);

		virtual void render();

	protected:
		friend class State;
		unsigned int order;
	};
}
