#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

#include "core.h"
#include "scene.h"



Fixture::Fixture(Vec2 position, float height, float width) : position(position) {
	rect.x = position.x;
	rect.y = position.y;
	rect.h = height;
	rect.w = width;
}

void Fixture::Draw(SDL_Renderer* renderer) {
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);

	// Set draw color to cyan
	SDL_SetRenderDrawColor(renderer, 0x0, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &rect);
}

KeyFixture::KeyFixture(Vec2 position, float height, float width, Mix_Chunk* sound) :
	Fixture(position, height, width), sound(sound) {}

void KeyFixture::Collide() const {
	Mix_PlayChannel(-1, sound, 0);
}

void KeyFixture::Update(float dt_ms) const {}

void KeyFixture::Draw(SDL_Renderer* renderer) {
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);

	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &rect);
}


// Entrance + Exit
// Keyboard

// TODO: produce per-level config?
std::vector<std::unique_ptr<Fixture>> InitScene(std::vector<Mix_Chunk*> sounds) {
	// Platform
	const float HORIZON_HEIGHT = 100;
	std::unique_ptr<Fixture> horizon = std::make_unique<Fixture>(Vec2(0, WINDOW_HEIGHT - HORIZON_HEIGHT), HORIZON_HEIGHT, WINDOW_WIDTH);

	// Walls
	const float WALL_HEIGHT_LEFT = WINDOW_HEIGHT - HORIZON_HEIGHT - 150;
	const float WALL_WIDTH = 50;
	std::unique_ptr<Fixture> leftWall = std::make_unique<Fixture>(Vec2(0, 0), WALL_HEIGHT_LEFT, WALL_WIDTH);

	const float WALL_HEIGHT_RIGHT = WINDOW_HEIGHT - HORIZON_HEIGHT - 150;
	std::unique_ptr<Fixture> rightWall = std::make_unique<Fixture>(Vec2(WINDOW_WIDTH - WALL_WIDTH, 0), WALL_HEIGHT_RIGHT, WALL_WIDTH);

	// TODO: Add keys
	const float KEY_HEIGHT = 100;
	const float KEY_WIDTH = 100;
	std::unique_ptr<Fixture> key_F_sharp = std::make_unique<KeyFixture>(Vec2(200, WINDOW_HEIGHT - HORIZON_HEIGHT - KEY_HEIGHT / 2),
		                                KEY_HEIGHT, KEY_WIDTH, sounds[0]);

	std::vector<std::unique_ptr<Fixture>> fixtures;
	fixtures.push_back(std::move(horizon));
	fixtures.push_back(std::move(leftWall));
	fixtures.push_back(std::move(rightWall));
	fixtures.push_back(std::move(key_F_sharp));
	printf("this is compiling\n");

	return fixtures;
}