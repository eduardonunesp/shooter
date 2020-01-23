#include "State.h"
#include <algorithm>
#include "Game.h"

namespace Thing2D {
	void State::add_timer(const std::string& timer_id, int time_limit_ms) {
		timers[timer_id] = new Timer(time_limit_ms);
		timers[timer_id]->reset();
	}
	
	void State::update() {
		std::for_each(timers.begin(), timers.end(), [&](auto timer) {
			timer.second->update(game->delta_time());
		});

		Group::update();
	}

	void State::destroy() {
		std::for_each(timers.begin(), timers.end(), [](auto timer) {
			delete timer.second;
		});

		Group::destroy();
	}
}