#pragma once

#include <vector>

namespace Thing2D {
	class Animation {
	public:
		Animation() :
			loop(false),
			ended(false),
			sum(0),
			anim_speed(1),
			curr_anim_frame(0) {}

		void set_current_frame(int frame);

		bool loop;
		bool ended;
		unsigned int sum;
		int anim_speed;
		int curr_anim_frame;
		std::vector<int> frames;
	};
}