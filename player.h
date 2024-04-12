#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <SDL.h>
#include "core.h"
#include "scene.h"

class Fixture;

const int PLAYER_HEIGHT = 80;
const int PLAYER_WIDTH = 15;
const float PLAYER_SPEED = 1.0;

const float JUMP_VELOCITY = -5.0;

class Player {
private:
	Vec2 position;
	Vec2 velocity;
	bool airborne;
	bool movingLeft;
	bool movingRight;

	// TODO: replace with a custom graphic with alpha-channel
	SDL_Rect rect{};

public:
	Player() = delete;
	Player(const Player&) = delete;
	explicit Player(Vec2 pos);

	void Move(SDL_Keycode sym);

	void StopMove(SDL_Keycode sym);

	void Jump();

	void Update(float dt_ms, const std::vector<std::unique_ptr<Fixture>>& fixtures);

	// Visual representation: square
	void Draw(SDL_Renderer* renderer);
};

#endif // PLAYER_H