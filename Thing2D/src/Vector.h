#pragma once

#include <iostream>
#include <math.h>

namespace Thing2D {
	class Vector {
	public:
		Vector() {
			x = 0;
			y = 0;
		}

		static Vector zero() { return Vector(0, 0); }
		static Vector up() { return Vector(0, -1); }
		static Vector down() { return Vector(0, 1); }
		static Vector right() { return Vector(1, 0); }
		static Vector left() { return Vector(-1, 0); }

		Vector(float x, float y) : x(x), y(y) {}

		int count() { return (int)sqrt(x * x + y * y); }

		Vector operator+(const Vector& v2) const { return Vector(x + v2.x, y + v2.y); }
		friend Vector& operator+=(Vector& v1, const Vector& v2) {
			v1.x += v2.x;
			v1.y += v2.y;

			return v1;
		}

		Vector operator-(const Vector& v2) const { return Vector(x - v2.x, y - v2.y); }
		friend Vector& operator-=(Vector& v1, const Vector& v2) {
			v1.x -= v2.x;
			v1.y -= v2.y;

			return v1;
		}

		Vector operator*(float scalar) {
			return Vector(x * scalar, y * scalar);
		}

		Vector& operator*=(float scalar) {
			x *= scalar;
			y *= scalar;

			return *this;
		}

		Vector operator/(float scalar) {
			return Vector(x / scalar, y / scalar);
		}

		Vector& operator/=(float scalar) {
			x /= scalar;
			y /= scalar;

			return *this;
		}

		void normalize() {
			int l = count();
			if (l > 0) {
				(*this) *= 1.0f / l;
			}
		}

		float x;
		float y;
	};
}
