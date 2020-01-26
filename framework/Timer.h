#pragma once

#include "SDL.h"
#include "Logger.h"

namespace Thing2D {
	class Timer {
	public:
		Timer(float time_limit):
			left_time(time_limit),
			time_limit(time_limit) {}

		void update(int delta_time) {
			left_time -= delta_time;
		}

		void set_time_limit(float new_time_limit) {
			left_time = new_time_limit;
		}

		void reset() {
			left_time = time_limit;
		}

		bool ended() {
			return left_time < 0;
		}

	protected:
		float left_time;
		float time_limit;
	};
}
