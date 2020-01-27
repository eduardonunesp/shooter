#include "Animation.h"

namespace Thing2D {
	void Animation::set_current_frame(int frame) {
		if (curr_anim_frame == frame) {
			return;
		}

		if (ended) {
			return;
		}

		if (!loop) {
			sum++;

			if (sum >= frames.size()) {
				ended = true;
			}
		}

		curr_anim_frame = frame;
	}
}