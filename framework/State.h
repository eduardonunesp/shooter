#pragma once

#include "map"
#include "string"
#include "Group.h"
#include "Timer.h"

namespace Thing2D {
	class GameObject;

	class State : public Group {
	public:
		State() : Group() {}

		void add_timer(const std::string& timer_id, int time_limit_ms);
		Timer* get_timer(const std::string& timer_id) {
			return timers[timer_id];
		}
		void update() override;
		void destroy() override;

	protected:
		friend class Game;

		std::map<std::string, Timer*> timers;
	};
}
