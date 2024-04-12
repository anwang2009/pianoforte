#include <chrono>
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_mixer.h>

#include "core.h"
#include "player.h"
#include "scene.h"

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_Window* window = SDL_CreateWindow("pianoforte", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
		return 1;
	}

	Mix_Chunk* F_sharp = Mix_LoadWAV("F_sharp.mp3");

	// Initialize game assets
	Player player(Vec2(70, 500));
	bool running = true;
	float dt_ms = 0;

	std::vector<Mix_Chunk*> sounds = { F_sharp };
	std::vector<std::unique_ptr<Fixture>> fixtures = InitScene(sounds);

	// Run game
	while (running) {
		auto startTime = std::chrono::high_resolution_clock::now();

		//int x;
		//std::cin >> x;

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			else if (event.type == SDL_KEYDOWN) {
				SDL_Keycode sym = event.key.keysym.sym;
				if (sym == SDLK_ESCAPE) {
					running = false;
				}
				else if (sym == SDLK_0) {
					Mix_PlayChannel(-1, F_sharp, 0);
				}
				else {
					// All other key actions should be routed to the player
					player.Move(sym);
				}
			}
			else if (event.type == SDL_KEYUP) {
				SDL_Keycode sym = event.key.keysym.sym;
				player.StopMove(sym);
			}
		}

		// Update game asset positions
		player.Update(dt_ms, fixtures);

		// Draw game assets
		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
		SDL_RenderClear(renderer);
		player.Draw(renderer);

		for (std::unique_ptr<Fixture>& fixture : fixtures) {
			fixture->Draw(renderer);
		}

		// Render
		SDL_RenderPresent(renderer);

		// Calculate frame time
		auto stopTime = std::chrono::high_resolution_clock::now();
		dt_ms = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
		dt_ms = 0.3;
	}

	// Cleanup
	Mix_FreeChunk(F_sharp);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_Quit();
	SDL_Quit();
	return 0;
}
