#ifndef CORE_H
#define CORE_H

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

// pixels / ms^2
const float GRAVITY = 0.05;

class Vec2 {
public:
	float x;
	float y;

	Vec2(): x(0.0), y(0.0) {}
	Vec2(float x, float y): x(x), y(y) {}

	Vec2 operator+(const Vec2& other);
	Vec2& operator+=(const Vec2& other);
	Vec2 operator*(float alpha);
};

#endif