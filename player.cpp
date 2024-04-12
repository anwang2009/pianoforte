#include <SDL.h>
#include <iostream>
#include <vector>

#include "core.h"
#include "player.h"
#include "scene.h"

Player::Player(Vec2 pos): position(pos), velocity(Vec2(0.0, 0.0)), airborne(false),
						  movingLeft(false), movingRight(false) {
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.x);
	rect.h = PLAYER_HEIGHT;
	rect.w = PLAYER_WIDTH;
}

void Player::Move(SDL_Keycode sym) {
	if (sym == SDLK_UP) {
		Jump();
	}
	else if (sym == SDLK_LEFT) {
		velocity.x = -PLAYER_SPEED;
		movingLeft = true;
	}
	else if (sym == SDLK_RIGHT) {
		velocity.x = PLAYER_SPEED;
		movingRight = true;
	}
}

void Player::StopMove(SDL_Keycode sym) {
	if (sym == SDLK_LEFT && movingLeft) {
		movingLeft = false;
		if (!movingRight) {
			velocity.x = 0;
		}
	}
	else if (sym == SDLK_RIGHT && movingRight) {
		movingRight = false;
		if (!movingLeft) {
			velocity.x = 0;
		}
	}
}

void Player::Jump() {
	if (!airborne) {
	    // initial velocity "up"
		velocity.y = JUMP_VELOCITY;
		airborne = true;
	}
}

void Player::Update(float dt_ms, const std::vector<std::unique_ptr<Fixture>>& fixtures) {
	position += velocity * dt_ms;

	// Check for top/bottom collisions
	if (position.y >= WINDOW_HEIGHT - PLAYER_HEIGHT) {
		position.y = WINDOW_HEIGHT - PLAYER_HEIGHT;
		velocity.y = 0;
		airborne = false;
	} else {
		if (position.y < 0) {
			position.y = 0;
		}
		velocity.y += GRAVITY * dt_ms;
	}

	// Check for collisions against fixtures

	for (const std::unique_ptr<Fixture>& fixture : fixtures) {
		float fixtureLeft = fixture->position.x;
		float fixtureRight = fixture->position.x + fixture->rect.w;
		float fixtureTop = fixture->position.y;
		float fixtureBottom = fixture->position.y + fixture->rect.h;

		float playerLeft = position.x;
		float playerRight = position.x + rect.w;
		float playerTop = position.y;
		float playerBottom = position.y + rect.h;

		
		if (playerLeft >= fixtureRight || playerRight <= fixtureLeft ||
			playerTop >= fixtureBottom || playerBottom <= fixtureTop) {
			//std::cout << "NOT COLLIDING" << std::endl;
			continue;
		}
		
		//printf("player %f,%f,%f,%f\n", playerLeft, playerRight, playerTop, playerBottom);
		//printf("fixture %f,%f,%f,%f\n", fixtureLeft, fixtureRight, fixtureTop, fixtureBottom);

		// Get minimum distance to any axis
		float dists[4] = {playerRight - fixtureLeft, fixtureRight - playerLeft,
		                  fixtureBottom - playerTop, playerBottom - fixtureTop};

		float min_positive_dist = FLT_MAX;
		int min_positive_dist_index = -1;

		for (size_t i = 0; i < 4; ++i) {
			float penetration = dists[i];
			if (penetration > 0 && penetration < min_positive_dist) {
				min_positive_dist = penetration;
				min_positive_dist_index = i;
			}
		}

		if (min_positive_dist_index < 0) {
			continue;
		}
		else {
			fixture->Collide(); 
			fixture->Update(dt_ms);
		}

		if (min_positive_dist_index == 0) {
			position.x -= dists[0];
			//velocity.x = 0;
			//std::cout << "x -= " << dists[0];
		}
		else if (min_positive_dist_index == 1) {
			position.x += dists[1];
			//velocity.x = 0;
			//std::cout << "x += " << dists[1];
		}
		else if (min_positive_dist_index == 2) {
			position.y += dists[2];
			velocity.y = 0;
			//std::cout << "y += " << dists[2];
		}
		else if (min_positive_dist_index == 3) {
			position.y -= dists[3];
			//std::cout << "y -= " << dists[3];
			velocity.y = 0;
			airborne = false;
		}
		else {
			std::cout << "err" << std::endl;
		}

	}
}

void Player::Draw(SDL_Renderer* renderer) {
	rect.x = static_cast<int>(position.x);
	rect.y = static_cast<int>(position.y);

	//std::cout << "player pos" << rect.x << "y" << rect.y << std::endl;
	// Set draw color to white
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &rect);
}
