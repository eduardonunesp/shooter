#pragma once

#include "Group.h"

namespace Thing2D {
	class State : public Group {
	public:
		State() : Group() {}
		virtual ~State() {};

		virtual const std::string& state_id() = 0;
	};
}