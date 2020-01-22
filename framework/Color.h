#pragma once

namespace Thing2D {
	class Color {
	public:
		Color() : r(0), g(0), b(0), a(0) {}
		Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
		int r, g, b, a;

		static Color red() { return Color(255, 0, 0, 255); }
		static Color green() { return Color(0, 255, 0, 255); }
		static Color blue() { return Color(0, 0, 255, 255); }
	};
}
