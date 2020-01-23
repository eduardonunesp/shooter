#pragma once

namespace Thing2D {
	class AnimationFrame {
	public:
		AnimationFrame(int x, int y) :
			row(x),
			col(y) {}

		int row;
		int col;
	};
}
