#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include "core.h"
#include "player.h"

class Fixture {
protected:
	Vec2 position;
	SDL_Rect rect{};

public:
	Fixture(Vec2 position, float height, float width);

	Fixture(const Fixture&) = delete;

	virtual void Collide() const {};

	virtual void Update(float dt_ms) const {};

	virtual void Draw(SDL_Renderer* renderer);

	friend class Player;
};

class KeyFixture : public Fixture {
private:
	Mix_Chunk* sound;

public:
	KeyFixture(Vec2 position, float height, float width, Mix_Chunk* sound);

    void Collide() const override;

	void Update(float dt_ms) const override;

	void Draw(SDL_Renderer* renderer) override;

};

std::vector<std::unique_ptr<Fixture>> InitScene(std::vector<Mix_Chunk*> sounds);

# endif