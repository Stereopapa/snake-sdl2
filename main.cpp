#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include <random>
#include <time.h>

#include <SDL.h>
#include "Game.h"

#define SCREEN_WIDTH	1024
#define SCREEN_HEIGHT	768

int initSDL(SDL_Window** window, SDL_Renderer** renderer) {
	int rc;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}
		
	//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, window, renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(*renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(*window, "198398 Patryk Piotrowski");

	SDL_ShowCursor(SDL_DISABLE);
	return 0;
}

void closeSDL(SDL_Renderer* renderer, SDL_Window* window) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {
	SDL_Event event;
	SDL_Window* window;
	SDL_Renderer* renderer;

	//sdl liblary usables init (renederer window settings)
	if (initSDL(&window, &renderer)) return 1;
	
	srand(time(0));
	Game game(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	game.startGame();

	while (!game.quit()) {
		game.renderFrame(renderer);
		game.handleControl(event);
		game.generateFrame();
	};

	closeSDL(renderer, window);
	return 0;
};
