#pragma once
#include "Timer.h"
#include "Info.h"
#include "Board.h"
#include "Snake.h"
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define TIME_TO_SPEEDUP 10

class Game
{
public:
	Game(SDL_Renderer* renderer, int sw, int sh);
	~Game();
	void renderFrame(SDL_Renderer* renderer);
	void generateFrame();
	void handleControl(SDL_Event& event);
	void startGame();
	enum class STATES {PLAYING, QUIT, LOOSE};
	STATES getState();
	bool playing();
	bool quit();
private:
	Timer* timer;
	Info* info;
	Board* board;
	Snake* snake;
	enum STATES state;
	int points;
};

