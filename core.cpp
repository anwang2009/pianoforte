#include "core.h"

Vec2 Vec2::operator+(const Vec2& other) {
	return Vec2(x + other.x, y + other.y);
}

Vec2& Vec2::operator+=(const Vec2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Vec2 Vec2::operator*(float alpha) {
	return Vec2(x * alpha, y * alpha);
}
