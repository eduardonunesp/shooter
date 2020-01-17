#pragma once

namespace Thing2D {
	class GameObject {
	public:
		virtual void Update() = 0;
		virtual void Draw() = 0;
	};
}